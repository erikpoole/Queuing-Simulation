default: 
	clang++ -c -std=c++11 main.cpp event.cpp
	clang++ -o queuingSimulation main.o event.o