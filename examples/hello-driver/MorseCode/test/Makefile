
obj-m += keymorse_test.cpp

#Zeus Framework files
obj-m += zeusbase/System/AbstractInputStream.cpp
obj-m += zeusbase/System/AbstractOutputStream.cpp
obj-m += zeusbase/System/BitCodedValue.cpp
obj-m += zeusbase/System/CriticalSection.cpp
obj-m += zeusbase/System/Directory.cpp
obj-m += zeusbase/System/DirectoryItem.cpp
obj-m += zeusbase/System/Event.cpp
obj-m += zeusbase/System/File.cpp
obj-m += zeusbase/System/FileInputStream.cpp
obj-m += zeusbase/System/FileOutputStream.cpp
obj-m += zeusbase/System/FilterInputStream.cpp
obj-m += zeusbase/System/FilterOutputStream.cpp
obj-m += zeusbase/System/Float.cpp
obj-m += zeusbase/System/GUIDWrapper.cpp
obj-m += zeusbase/System/Int.cpp
obj-m += zeusbase/System/String.cpp
obj-m += zeusbase/System/StringList.cpp
obj-m += zeusbase/System/StringTokenizer.cpp
obj-m += zeusbase/System/SynchronizeObject.cpp
obj-m += zeusbase/System/TextInputStream.cpp
obj-m += zeusbase/System/Thread.cpp
obj-m += zeusbase/System/ThreadManager.cpp
obj-m += zeusbase/System/ThreadMessageQueue.cpp
obj-m += zeusbase/System/Time.cpp
obj-m += zeusbase/System/ZObject.cpp

#Needed libraries for Zeus Framework code
ZEUS_LIB = -lpthread -ldl -lm -luuid
ZEUS_FLAGS = -D_UNICODE -DUNICODE

OUT_FILE = keymorse_test

modules:
	g++ $(obj-m) -o$(OUT_FILE) -I. -Izeusbase $(ZEUS_LIB) $(ZEUS_FLAGS)

clean:
	rm -f .*.cmd *.o
