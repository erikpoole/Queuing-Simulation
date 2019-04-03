default: 
	clang++ -c -std=c++11 main.cpp event.cpp line.cpp customer.cpp
	clang++ -o simulator main.o event.o line.o customer.o

clean:
	rm *.o
	rm simulator