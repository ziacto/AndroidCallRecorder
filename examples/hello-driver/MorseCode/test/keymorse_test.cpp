#include "stdio.h"
#include <zeusbase/System/TextInputStream.h>
#include <zeusbase/System/FileOutputStream.h>
#include <zeusbase/System/StringTokenizer.h>
#include <zeusbase/System/Thread.h>
#include <zeusbase/System/Time.h>

USING_NAMESPACE_Zeus

/*************************************************************************/
/*! Status structure of the driver
*/
/*************************************************************************/
struct TypeDriverState
{
  int iTime;
  int iBufferSize;
  int iFreeSize;
  int iDataSize;
};

/*************************************************************************/
/*! Gets the status of the driver
*/
/*************************************************************************/
void getDriverStatus(TypeDriverState& rState)
{
  rState.iTime       = 0;
  rState.iBufferSize = 0;
  rState.iFreeSize   = 0;
  rState.iDataSize   = 0;
  TAutoPtr<TTextInputStream> ptrStream = new TTextInputStream(TString(L"/proc/keymorse"), TTextInputStream::etISO_8859_1);

  TString strText;
  while (ptrStream->readLine(strText) == RET_NOERROR)
  {
    TStringTokenizer Tokenizer(strText, L" ", true);
    TString strType  = Tokenizer.getNextToken();
    TString strValue = Tokenizer.getNextToken();

    if (strType.equals(L"Blinktime"))
    {
      rState.iTime = strValue.toInt();
    }
    else if (strType.equals(L"TotalMem"))
    {
      rState.iBufferSize = strValue.toInt();
    }
    else if (strType.equals(L"FreeMem"))
    {
      rState.iFreeSize = strValue.toInt();
    }
    else if (strType.equals(L"DataMem"))
    {
      rState.iDataSize = strValue.toInt();
    }
  }
}

/*************************************************************************/
/*! Prints the status
*/
/*************************************************************************/
void printStatus(TypeDriverState& rState)
{
  printf("State of the driver is:\n");
  printf("  Time interval : %d [ms]\n",    rState.iTime);
  printf("  Total Memory  : %d [Bytes]\n", rState.iBufferSize);
  printf("  Free Memory   : %d [Bytes]\n", rState.iFreeSize);
  printf("  Buffered Data : %d [Bytes]\n", rState.iDataSize);
}


/*************************************************************************/
/*! Sends data to the driver
*/
/*************************************************************************/
void sendDataToDriver(const TString& rData)
{
  TAutoPtr<TFileOutputStream> ptrStream = new TFileOutputStream(TString(L"/dev/mo0"), false);
  ptrStream->write(rData.c_str(NULL), rData.getSize());
}

/*************************************************************************/
/*! reads the processed data
*/
/*************************************************************************/
void readProcessedData(TString& rData)
{
  rData = L"";
  TAutoPtr<TTextInputStream> ptrStream = new TTextInputStream(TString(L"/proc/keymorse_test"), TTextInputStream::etISO_8859_1);
  TString strText;
  while (ptrStream->readLine(strText) == RET_NOERROR)
  {
    rData += strText;
  }
}


/*************************************************************************/
/*! waits until the buffer of the driver is empty
*/
/*************************************************************************/
void waitForComplete()
{
  TypeDriverState DriverState;
  do
  {
    getDriverStatus(DriverState);
    TTime::sleep(0.3);
    printf(".", DriverState.iFreeSize, DriverState.iBufferSize);
    fflush(stdout);
  } while(DriverState.iBufferSize != DriverState.iFreeSize);
}

/*************************************************************************/
/*! tests the processed data of the driver
*/
/*************************************************************************/
void testData(const TString& rData)
{
  waitForComplete();

  TString strTestData;
  readProcessedData(strTestData);
  if (strTestData.equalsStr(rData))
  {
    printf("ok\n");
  }
  else
  {
    printf("failed[Expected %s; received %s]\n", rData.c_str(NULL), strTestData.c_str(NULL));
  }
}

/*************************************************************************/
/*! Test thread 
*/
/*************************************************************************/
class TDriverTestThread : public TThread
{
  public:
    TDriverTestThread(const TString& rData)
     : TThread(), 
       m_strData(rData)
    {
    }

  protected:
    virtual ~TDriverTestThread() {}

    //Method of TThread
    virtual void MQUALIFIER execute()
    {
      sendDataToDriver(m_strData);
    }

  private:
    ///Data
    TString m_strData;
};



/*************************************************************************/
/*! Main entry of the test
*/
/*************************************************************************/
int main()
{
  printf("Test application for keymorse module\n");
  printf("b_hadorn@bluewin.ch\n\n");

  //----------------------------------------------------------------
  // Test the current driver state
  // TEST OF REQUIREMENT 7
  TypeDriverState DriverState;
  getDriverStatus(DriverState);
  printStatus(DriverState);
  if (DriverState.iTime != 10)
  {
    printf("Configuration Error. BlinkTime interval must be set to 10 [Current value = %d]\n", DriverState.iTime);
    return 1;
  } 
  else if (DriverState.iBufferSize != 32)
  {
    printf("Configuration Error. Buffer size must be set to 32 Bytes [Current value = %d]\n", DriverState.iBufferSize);
    return 1;
  } 


  //----------------------------------------------------------------
  // TEST OF REQUIREMENT 1, 5 AND 6
  TString strData(L'T', 40);
  TString strTestData;

  sendDataToDriver(strData);
  testData(strData);

  //----------------------------------------------------------------
  // TEST OF REQUIREMENT 2
  TString strData1(L'E', 32);
  TString strData2(L'A', 32);
  TString strData3(L'T', 32);
  TAutoPtr<TDriverTestThread> ptrThread1 = new TDriverTestThread(strData1);
  TAutoPtr<TDriverTestThread> ptrThread2 = new TDriverTestThread(strData2);
  TAutoPtr<TDriverTestThread> ptrThread3 = new TDriverTestThread(strData3);
  ptrThread1->start();
  TTime::sleep(0.3);
  ptrThread2->start();
  TTime::sleep(0.3);
  ptrThread3->start();
  TTime::sleep(0.3);

  //all threads should be busy now
  if (ptrThread2->isDead() ||
      ptrThread3->isDead())
  {
    printf("failed. Thread 2 and 3 must be blocking.\n");
  }
  else
  {
    testData(strData1 + strData2 + strData3);
  }
  return 0;
} 
