CC=g++
FLAGS=-std=c++11
LD=-lpthread
bin=pthreadpool
src=ThreadPoolTest.cc

$(bin):$(src)
	$(CC) -o $@ $^ $(LD) $(FLAGS)
.PHONY:clean
clean:
	rm -f $(bin)