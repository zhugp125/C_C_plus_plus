Target = Singleton
cc = g++
deps = Singleton.hpp
obj = main.o

$(Target) : $(obj)
	$(cc) -o $(Target) $(obj) -I/usr/local/include /usr/local/lib/libboost_thread.a

main.o : main.cpp $(deps)
	$(cc) -c main.cpp

.PHONY : clean
clean :
	rm $(Target) $(obj)

