# makefile

# uncomment the version of the compiler that you are using
#clang++ is for Mac OS
# C++ = clang++ -std=c++11
# g++ is for most Linux
C++ = g++ -std=c++11

# .DEFAULT_GOAL := all

all: clean client server sync_test_pcbuffer

clean:
	rm -f *.o server client fifo* sync_test_mutex sync_test_mg sync_test_semaphore sync_test_pcbuffer

# Part 1 & 2
reqchannel.o: reqchannel.hpp reqchannel.cpp
	$(C++) -c -g reqchannel.cpp

server: dataserver.cpp reqchannel.o
	$(C++) -o server dataserver.cpp reqchannel.o -lpthread

client: client.cpp reqchannel.o pcbuffer.o semaphore.o
	$(C++) -o client client.cpp reqchannel.o pcbuffer.o semaphore.o -lpthread

# simpleclient: simpleclient.cpp reqchannel.o
# 	$(C++) -o simpleclient simpleclient.cpp reqchannel.o


# Part 3 & 4

# test_suite: sync_test_mutex sync_test_mg sync_test_semaphore sync_test_pcbuffer

mutex.o: mutex.hpp mutex.cpp
	$(C++) -c -g mutex.cpp

mutex_guard.o: mutex_guard.hpp mutex_guard.cpp
	$(C++) -c -g mutex_guard.cpp

semaphore.o: semaphore.hpp semaphore.cpp
	$(C++) -c -g semaphore.cpp

pcbuffer.o: pcbuffer.hpp pcbuffer.cpp
	$(C++) -c -g pcbuffer.cpp

# sync_test_mutex: sync_test.cpp mutex.o
# 	$(C++) -o sync_test_mutex sync_test.cpp mutex.o -lpthread
# #
# sync_test_mg: sync_test.cpp mutex.o mutex_guard.o
# 	$(C++) -o sync_test_mg sync_test.cpp mutex.o mutex_guard.o -lpthread
# #
# sync_test_semaphore: sync_test.cpp mutex.o mutex_guard.o semaphore.o
# 	$(C++) -o sync_test_semaphore sync_test.cpp mutex.o mutex_guard.o semaphore.o -lpthread

sync_test_pcbuffer: sync_test.cpp pcbuffer.o mutex.o mutex_guard.o semaphore.o
	$(C++) -o sync_test_pcbuffer sync_test.cpp pcbuffer.o mutex.o mutex_guard.o semaphore.o -lpthread


