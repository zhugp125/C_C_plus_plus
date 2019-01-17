Target = RingBuffer
cc = g++
deps = RingBuffer.hpp
obj = main.o

$(Target) : $(obj)
	$(cc) -o $(Target) $(obj) -std=c++11

$(obj) : main.cpp $(deps)
	$(cc) -c main.cpp

.PHONY : clean
clean :
	rm $(Target) $(obj)
