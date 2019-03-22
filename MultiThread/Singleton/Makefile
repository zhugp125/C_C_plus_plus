Target = Singleton
cc = g++
deps = singleton.hpp
obj = main.o

$(Target) : $(obj)
	$(cc) -o $(Target) $(obj) -I/usr/local/include -std=c++11

main.o : main.cpp $(deps)
	$(cc) -c main.cpp

.PHONY : clean
clean :
	rm $(Target) $(obj)

