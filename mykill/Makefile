.PHONY:all
all:mykill myproc


mykill:mykill.cc
	g++ -o $@ $^ -g -std=c++11

myproc:myproc.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f mykill myproc