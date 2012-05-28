/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 ***************************************************************************
 * Projekt : Operation System Project
 * Module  : keymorse
 * Package : Drivers
 * Author  : Benjamin Hadorn
 * Datum   : $Date$
 * Ablage  : $File$
 * System  : Zeus C++ Framework
 ***************************************************************************
 * Licence:                                                                *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version             *
 *   2.1 of the License, or (at your option) any later version.            *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  *
 ***************************************************************************/

/***************************************************************************
 Changes :
 $Log$
***************************************************************************/

#include "keymorse.h"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/kthread.h>
#include <linux/kfifo.h>
#include <linux/wait.h>

#include <linux/vt_kern.h>  //for fg_console
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/proc_fs.h> //used to access the proc file system
#include <asm/uaccess.h>   //used for copy_from_user
#include <asm/atomic.h>    //used for atomic operations


//#######################################################################
//                     DECLARATION
//License
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benjamin Hadorn");
MODULE_DESCRIPTION("Morse code blink module for key board");
MODULE_SUPPORTED_DEVICE("testdevice");

//------------------------------------------
//Parameters
///Blink time
static int BlinkTime      = 50;
///Buffer size of the FIFO (2^n)
static int BufferSize     = 5;
///Major device number
static int Mo_Major       = KEYMORSE_MAJOR;
///Minor start number 
static int Mo_Minor       = 0;
///Number of devices
static int Mo_Dev_Numbers = 3;


//parameter export
module_param(BlinkTime,  int, S_IRUGO);
module_param(BufferSize, int, S_IRUGO);
module_param(Mo_Major,   int, S_IRUGO);

MODULE_PARM_DESC(BlinkTime,  "Time of blinking in [ms]");
MODULE_PARM_DESC(BufferSize, "Size of the buffer. If BufferSize=5 -> 2^5 = 32 Bytes");
MODULE_PARM_DESC(Mo_Major,   "Device major number");



//------------------------------------------
// DATA TYPES
/// This structure defines an internal data wrapper for morse data
struct TypeMorseDevice
{
  struct cdev         cdev;
  struct task_struct* pThread;
  struct kfifo*       pFifo;
  struct semaphore    lockMutex;
  struct semaphore    lockWriter;
  char*               pcFifoBuffer;
  struct tty_driver*  pTTYDriver;
};

///Queue for reader
DECLARE_WAIT_QUEUE_HEAD(queueReader);
///Queue for writer
DECLARE_WAIT_QUEUE_HEAD(queueWriter);

///Item to transform a ASCII to the morse alphabet
struct TypeMorseItem
{
  char cLength;
  char cCode;
};


//------------------------------------------
// VARIABLES

///Variable to handle the data
static struct TypeMorseDevice g_MorseDevice;
///Variable to store file operations
static struct file_operations g_Main_fops =
  {
    .write   = main_write,
    .open    = main_open,
    .release = main_release,
    .owner   = THIS_MODULE,
  };

///ID of the device driver
static dev_t g_devID;
/// Mapping of the whole alphabet
static struct TypeMorseItem g_acDataMap[59] = {
{ /*32   */  0, 0x00 },
{ /*33 ! */  5, 0x06 }, //00110
{ /*34 " */  6, 0x12 }, //010010
{ /*35 # */  0, 0x00 }, 
{ /*36 $ */  0, 0x00 }, 
{ /*37 % */  0, 0x00 }, 
{ /*38 & */  0, 0x00 }, 
{ /*39 ' */  6, 0x1E }, //011110
{ /*40 ( */  0, 0x00 }, 
{ /*41 ) */  0, 0x00 }, 
{ /*42 * */  0, 0x00 }, 
{ /*43 + */  0, 0x00 }, 
{ /*44 , */  6, 0x33 }, //110011
{ /*45 - */  0, 0x00 }, 
{ /*46 . */  6, 0x16 }, //010101 
{ /*47 / */  0, 0x00 }, 
{ /*48 0 */  5, 0x1F }, //11111
{ /*49 1 */  5, 0x0F }, //01111
{ /*50 2 */  5, 0x07 }, //00111
{ /*51 3 */  5, 0x03 }, //00011
{ /*52 4 */  5, 0x01 }, //00001
{ /*53 5 */  5, 0x00 }, //00000
{ /*54 6 */  5, 0x10 }, //10000
{ /*55 7 */  5, 0x18 }, //11000
{ /*56 8 */  5, 0x1C }, //11100
{ /*57 9 */  5, 0x1E }, //11110
{ /*58 : */  6, 0x38 }, //111000
{ /*59 ; */  0, 0x00 }, 
{ /*60 < */  0, 0x00 }, 
{ /*61 = */  5, 0x11 }, //10001 
{ /*62 > */  0, 0x00 }, 
{ /*63 ? */  6, 0x0C }, //001100 
{ /*64 @ */  0, 0x00 }, 
{ /*65 A */  2, 0x01 }, //01
{ /*66 B */  4, 0x08 }, //1000
{ /*67 C */  4, 0x0A }, //1010
{ /*68 D */  3, 0x04 }, //100
{ /*69 E */  1, 0x00 }, //0
{ /*70 F */  4, 0x02 }, //0010
{ /*71 G */  3, 0x06 }, //110
{ /*72 H */  4, 0x00 }, //0000
{ /*73 I */  2, 0x00 }, //00
{ /*74 J */  4, 0x07 }, //0111
{ /*75 K */  3, 0x05 }, //101
{ /*76 L */  4, 0x04 }, //0100
{ /*77 M */  2, 0x03 }, //11
{ /*78 N */  2, 0x02 }, //10
{ /*79 O */  3, 0x07 }, //111
{ /*80 P */  4, 0x06 }, //0110
{ /*81 Q */  4, 0x0D }, //1101
{ /*82 R */  3, 0x02 }, //010
{ /*83 S */  3, 0x00 }, //000
{ /*84 T */  1, 0x01 }, //1
{ /*85 U */  3, 0x01 }, //001
{ /*86 V */  4, 0x01 }, //0001
{ /*87 W */  3, 0x03 }, //011
{ /*88 X */  4, 0x09 }, //1001
{ /*89 Y */  4, 0x0B }, //1011
{ /*90 Z */  4, 0x0C }  //1100
};
///Number of bytes not yet processed
static atomic_t g_atomUnprocessedData = ATOMIC_INIT(0);


//Variables to test the driver. The variables are protected 
// by g_MorseDevice.lockMutex
#ifdef TEST_DRIVER
static int g_iTestBufferIndex = 0;
static char g_acTestBuffer[100];
#endif


//#######################################################################
//                         FUNCTIONS OF READER THERAD

/*************************************************************************/
/*! sends the morse code to the key board driver
    \param pDev   : morse device
    \param cASCII : ASCII code
*/
/*************************************************************************/
static void sendCode(struct TypeMorseDevice* pDev, char cASCII)
{
  struct TypeMorseItem Item;
  int i = 0;
  int iLong = 0;

  printk(KERN_NOTICE "mo 0-2:   Sending char code: %d\n", cASCII);

  //Make sure the border are met.
  if (cASCII < 32) { cASCII = 32; }
  if (cASCII > 90)
  {
    // Convert lower case to upper case
    if (cASCII >= 97 && cASCII <= 122)
    {
      cASCII -= 32;
    }
    else
    {
      cASCII = 32;
    } 
  }
  Item = g_acDataMap[cASCII-32];

  if (pDev->pTTYDriver != NULL && Item.cLength > 0)
  {
    set_current_state(TASK_INTERRUPTIBLE);
    //Break from one character to the other one (+BlinkTime from the last send character)
    schedule_timeout(2*BlinkTime);
    for (i = Item.cLength-1; i >= 0; i--)
    {
      iLong = (Item.cCode & (1 << i));
      (pDev->pTTYDriver->ioctl)(vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, LED_SCR | LED_NUM | LED_CAP);  //Capslock

      // Long term blinking
      if (iLong)
      {
        set_current_state(TASK_INTERRUPTIBLE);
        schedule_timeout(3*BlinkTime);
      }

      //Short term blinking
      else
      {
        set_current_state(TASK_INTERRUPTIBLE);
        schedule_timeout(BlinkTime);
      }

      //Turn the light off
      (pDev->pTTYDriver->ioctl)(vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, 0xFF); //restore
      set_current_state(TASK_INTERRUPTIBLE);
      schedule_timeout(BlinkTime);
    }
  }
}

/*************************************************************************/
/*! This runs the morse thread, witch will convert and send all data
    to the keyboard
*/
/*************************************************************************/
static int run_morse(void* pData)
{
  struct TypeMorseDevice* pDev  = (struct TypeMorseDevice*)pData;
  int iRetval = 0;

  if (pDev != NULL)
  {
    printk(KERN_WARNING "mo 0-2: Thread started...\n");

    set_current_state(TASK_INTERRUPTIBLE);
    while(!kthread_should_stop())
    {
      //1. check if there is data to write
      set_current_state(TASK_INTERRUPTIBLE);
      iRetval = wait_event_interruptible(queueReader, (pDev->pFifo->in - pDev->pFifo->out > 0 || kthread_should_stop()));

      //2. check error and try to get the fifo lock
      set_current_state(TASK_INTERRUPTIBLE);
      if (iRetval == 0 && !kthread_should_stop() && down_interruptible(&pDev->lockMutex) == 0)
      {
        //3. Read data and release the lock
        char acBuffer[1];
        __kfifo_get(pDev->pFifo, acBuffer, 1);


#ifdef TEST_DRIVER
        g_acTestBuffer[g_iTestBufferIndex] = acBuffer[0];
        g_iTestBufferIndex += 1;
        if (g_iTestBufferIndex >= 100)
        {
          g_iTestBufferIndex = 0;
        }
#endif

        up(&pDev->lockMutex);

        //4. wake up all writers
        wake_up_interruptible(&queueWriter);

        //5. send character as morse code to keyboard
        sendCode(pDev, acBuffer[0]);
        atomic_dec(&g_atomUnprocessedData);
      } //(down_interruptible(&pDev->lockMutex) == 0)
    }
    __set_current_state(TASK_RUNNING);
    printk(KERN_WARNING "mo 0-2: Thread ended.\n");
  } //(pDev != NULL)

  return 0;
}




//#######################################################################
//                       FUNCTIONS OF WRITER THREAD

/*************************************************************************/
/*! writes the data to the fifo
*/
/*************************************************************************/
static void writeData(struct TypeMorseDevice* pDevice, char* pcBuffer, int iSize)
{
  char acChar[2] = { 0, 0};
  int i          = 0;
  int iRetval    = 0;

  printk(KERN_NOTICE "mo 0-2: writeData() - ");
  while(i < iSize)
  { 
    //1. Check if there is space available to write
    iRetval = wait_event_interruptible(queueWriter, 
                                       (pDevice->pFifo->size - pDevice->pFifo->in + pDevice->pFifo->out > 0));

    //2. get fifo lock
    if (iRetval == 0 && down_interruptible(&pDevice->lockMutex) == 0)
    {
      printk(KERN_NOTICE ".%d", pDevice->pFifo->size - pDevice->pFifo->in + pDevice->pFifo->out);

      //3. Send data and release fifo lock
      while(i < iSize && pDevice->pFifo->size - pDevice->pFifo->in + pDevice->pFifo->out > 0)
      {
        acChar[0] = pcBuffer[i];
        __kfifo_put(pDevice->pFifo, acChar, 1);
        i++;
      }
      up(&pDevice->lockMutex);

      //4. wake the reader
      wake_up_interruptible(&queueReader);
    }

    //Error
    else
    {
      //Just to be sure the unprocessed data equals the 
      // number of bytes when we entered the function
      atomic_sub(iSize -i, &g_atomUnprocessedData);

      i = iSize;
      printk(KERN_NOTICE "Proceeding interrupted (2)\n");
    }
  }
}


/*************************************************************************/
/*! Used to write data to the device
*/
/*************************************************************************/
/*static*/ ssize_t main_write(struct file* pFile, const char __user* pcUserData, size_t iSize, loff_t* piPos)
{
  int iRetval = -EFAULT;
  struct TypeMorseDevice* pDevice = (struct TypeMorseDevice*)pFile->private_data;

  if (pDevice == NULL)
  {
    iRetval = -EPIPE;
    printk(KERN_NOTICE "mo 0-2: write() - No device found\n");
  }
  else if (iSize > 0)
  { 
    char* pcBuffer = kmalloc((iSize+1)*sizeof(char), GFP_KERNEL);
    if (pcBuffer != NULL)
    {
      memset(pcBuffer, 0, iSize*sizeof(char));
      if (copy_from_user(pcBuffer, pcUserData, iSize) == 0)
      {
        pcBuffer[iSize] = 0x00;
        iRetval = -ERESTARTSYS;

        //////////////////////////////////////////////////////// 
        atomic_add(iSize, &g_atomUnprocessedData);
        if (down_interruptible(&pDevice->lockWriter) == 0)
        {
          printk(KERN_NOTICE "mo 0-2: write() - Proceed with data: %s (Size=%d)\n", pcBuffer, iSize);
          writeData(pDevice, pcBuffer, iSize);
          up(&pDevice->lockWriter);
          iRetval = iSize;
        } //down_interruptible(&pDevice->lockWriter) == 0
        else
        {
          //Could not aquire the write lock (interrupted)
          // -> decrement the unprocessed data size
          atomic_sub(iSize, &g_atomUnprocessedData);
          printk(KERN_NOTICE "mo 0-2: write() - Proceeding interrupted (1)\n");
        } 
        //////////////////////////////////////////////////////// 

      } //(copy_from_user(pcBuffer, pcUserData, iSize) == 0)
      else
      {
        printk(KERN_NOTICE "mo 0-2: write() - Could not copy from user\n");
        iRetval = -EFAULT;
      }
      kfree(pcBuffer);
    } //(pcBuffer != NULL)
    else
    {
      iRetval = -ENOMEM;
    }
  }
  else 
  {
    printk(KERN_NOTICE "mo 0-2: write() - Empty string passed\n");
  }
  return iRetval;
}

/*************************************************************************/
/*! Opens the device
*/
/*************************************************************************/
/*static*/ int main_open(struct inode* pNode, struct file* pFile)
{
  struct TypeMorseDevice* pDevice;

  printk(KERN_NOTICE "mo 0-2: open() - device opened\n");
  pDevice             = container_of(pNode->i_cdev, struct TypeMorseDevice, cdev);
  pFile->private_data = pDevice;
  return 0;
}

/*************************************************************************/
/*! Closes the device
*/
/*************************************************************************/
/*static*/ int main_release(struct inode* pNode, struct file* pFile)
{
  return 0;
}




//#######################################################################
//                       REGISTRATION AND RELEASE

/*************************************************************************/
/*! Initialisation function of the key morse module. This is called
    when the module is loaded by the kernel
*/
/*************************************************************************/
static int initModule(void)
{
  int iRetval         = 0;
  int iIndex          = 0;
  int iFifoBufferSize = 0;

  g_MorseDevice.pThread      = NULL;
  g_MorseDevice.pFifo        = NULL;
  g_MorseDevice.pcFifoBuffer = NULL;

  //Check parameter bounds
  if (BlinkTime < 10)
  {
    BlinkTime = 10;
  }
  if (BufferSize < 3)
  {
    BufferSize = 3;
  }
  else if (BufferSize > 10)
  {
    BufferSize = 10;
  }
  printk(KERN_NOTICE "mo 0-2: Starting morse code module..\n");
  printk(KERN_NOTICE "mo 0-2:   Parameter Blinktime  = [%d]\n", BlinkTime);
  printk(KERN_NOTICE "mo 0-2:   Parameter BufferSize = [%d]\n", BufferSize);
  printk(KERN_NOTICE "mo 0-2:   Parameter Mo_Major   = [%d]\n", Mo_Major);


  //Registers the character device
  if (Mo_Major > 0)
  {
    g_devID = MKDEV(Mo_Major, Mo_Minor);
    iRetval = register_chrdev_region(g_devID, Mo_Dev_Numbers, KEYMORSE_NAME);
  }
  else
  {
    iRetval = alloc_chrdev_region(&g_devID, Mo_Minor, Mo_Dev_Numbers, KEYMORSE_NAME);
    Mo_Major = MAJOR(g_devID);
  }

  if (iRetval != 0)
  {
    printk(KERN_WARNING "mo 0-2: Cant get the major number = [%d]\n", Mo_Major);
    printk(KERN_WARNING "mo 0-2: Error registring the driver. Error=[%d]\n", iRetval);
  }
  else
  {
    printk(KERN_NOTICE "mo 0-2: Device registered. Major=[%d]\n", Mo_Major); 

    //Registers the device methods and adds them to the kernel
    iRetval = setup_cdev(&g_MorseDevice, iIndex);
    if (iRetval != 0)
    {
      printk(KERN_WARNING "mo 0-2: Error adding mo%d. Error=[%d]\n", iIndex, iRetval);
    }

    //create fifo and create thread
    else
    {
      iFifoBufferSize = 0x1 << BufferSize;

      atomic_set(&g_atomUnprocessedData, 0);

      g_MorseDevice.pcFifoBuffer = kmalloc(iFifoBufferSize*sizeof(char), GFP_KERNEL);
      g_MorseDevice.pFifo        = kfifo_init(g_MorseDevice.pcFifoBuffer, iFifoBufferSize, GFP_KERNEL, NULL);
      g_MorseDevice.pTTYDriver   = vc_cons[fg_console].d->vc_tty->driver;

      init_waitqueue_head(&queueReader);
      init_waitqueue_head(&queueWriter);
      sema_init(&g_MorseDevice.lockMutex,       1);
      sema_init(&g_MorseDevice.lockWriter,      1);

      //initialize the proc file 
      create_proc_read_entry(KEYMORSE_NAME, 0, NULL, read_morsemem, NULL);

#ifdef TEST_DRIVER
      create_proc_read_entry("keymorse_test", 0, NULL, read_morsetest, NULL);
#endif

      //start the morse thread
      g_MorseDevice.pThread = kthread_run(run_morse, &g_MorseDevice, "morse_thread");
      if (IS_ERR(g_MorseDevice.pThread))
      {
        printk(KERN_WARNING "mo 0-2: Error creating the morse_thread_xx\n");
        iRetval = -EAGAIN;
      }
    }
  }
  return iRetval;
}

/*************************************************************************/
/*! exit function of the key morse module. This is called
    when the module is unloaded by the kernel
*/
/*************************************************************************/
static void exitModule(void)
{
  if (Mo_Major > 0)
  {
    unregister_chrdev_region(g_devID, Mo_Dev_Numbers);
    release_cdev(&g_MorseDevice);
  }

  if (g_MorseDevice.pThread != NULL)
  {
    kthread_stop(g_MorseDevice.pThread);
    g_MorseDevice.pThread = NULL;
  }

  if (g_MorseDevice.pcFifoBuffer != NULL)
  {
    kfree(g_MorseDevice.pcFifoBuffer);
    g_MorseDevice.pcFifoBuffer= NULL;
  }

  //Remove the proc entry
  remove_proc_entry(KEYMORSE_NAME, NULL);

#ifdef TEST_DRIVER
  remove_proc_entry("keymorse_test", NULL);
#endif

  printk(KERN_NOTICE "mo 0-2: Exiting module\n");
}

/*************************************************************************/
/*! this function registers the main functions of the device
*/
/*************************************************************************/
static int setup_cdev(struct TypeMorseDevice* pData, int iIndex)
{
  int iDeviceNo = MKDEV(Mo_Major, Mo_Minor + iIndex);

  cdev_init(&pData->cdev, &g_Main_fops);
  pData->cdev.owner = THIS_MODULE;
  pData->cdev.ops   = &g_Main_fops;

  return cdev_add(&pData->cdev, iDeviceNo, 1);
}

/*************************************************************************/
/*! this function releases the device data
*/
/*************************************************************************/
static void release_cdev(struct TypeMorseDevice* pData)
{
  cdev_del(&pData->cdev);
}


/*************************************************************************/
/*! Reads the data for proc mem file
*/
/*************************************************************************/
/*static*/ int read_morsemem(char* pcBuffer, char** ppcStart, off_t iOffset, int iCount, int* piEOF, void* pData)
{
  int iLen = 0;
  if (down_interruptible(&g_MorseDevice.lockMutex) == 0)
  {
    iLen += sprintf(pcBuffer + iLen, "MorseCodeDriver %d.%d\n", Mo_Major, Mo_Minor);
    iLen += sprintf(pcBuffer + iLen, "Blinktime %d [ms]\n", BlinkTime);
    iLen += sprintf(pcBuffer + iLen, "TotalMem  %d [Bytes]\n", g_MorseDevice.pFifo->size);
    iLen += sprintf(pcBuffer + iLen, "FreeMem   %d [Bytes]\n", g_MorseDevice.pFifo->size - g_MorseDevice.pFifo->in + g_MorseDevice.pFifo->out);
    iLen += sprintf(pcBuffer + iLen, "DataMem   %d [Bytes]\n", atomic_read(&g_atomUnprocessedData));
    up(&g_MorseDevice.lockMutex);
  }
  *piEOF = 1;
  return iLen;
}

#ifdef TEST_DRIVER
/*************************************************************************/
/*! reads the processed data for testing the output sequence
*/
/*************************************************************************/
/*static*/ int read_morsetest(char* pcBuffer, char** ppcStart, off_t iOffset, int iCount, int* piEOF, void* pData)
{
  int iLen = 0;
  if (down_interruptible(&g_MorseDevice.lockMutex) == 0)
  {
    if (g_iTestBufferIndex > 0)
    {
      memcpy(pcBuffer, g_acTestBuffer, g_iTestBufferIndex);
      iLen = g_iTestBufferIndex;
      g_iTestBufferIndex = 0;
    }
    up(&g_MorseDevice.lockMutex);
  }
  *piEOF = 1;
  return iLen;
}

#endif

//Hooks
module_init(initModule);
module_exit(exitModule);

