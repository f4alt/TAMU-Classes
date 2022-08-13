# makefile

# uncomment the version of the compiler that you are using
# clang++ is for Mac OS
# C++ = clang++ -std=c++11
# g++ is for most Linux
C++ = /usr/bin/g++ -std=c++11

.DEFAULT_GOAL := all

clean:
	rm -f *.o client dataserver fifo*

all: dataserver client

dataserver: dataserver.cpp netreqchannel.o
	$(C++) -o dataserver dataserver.cpp netreqchannel.o -lpthread

client: client.cpp netreqchannel.o pcbuffer.o semaphore.o
	$(C++) -o client client.cpp netreqchannel.o pcbuffer.o semaphore.o -lpthread

netreqchannel.o: netreqchannel.hpp netreqchannel.cpp
	$(C++) -c -g netreqchannel.cpp

pcbuffer.o: pcbuffer.hpp pcbuffer.cpp
	$(C++) -c -g pcbuffer.cpp

semaphore.o: semaphore.hpp semaphore.cpp
	$(C++) -c -g semaphore.cpp

# test_suite: sync_test_semaphore sync_test_pcbuffer
#
# sync_test_semaphore: sync_test.cpp semaphore.o
# 	$(C++) -o sync_test_semaphore sync_test.cpp semaphore.o -lpthread
#
# sync_test_pcbuffer: sync_test.cpp pcbuffer.o semaphore.o
# 	$(C++) -o sync_test_pcbuffer sync_test.cpp pcbuffer.o semaphore.o -lpthread
