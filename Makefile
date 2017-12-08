main: Combinator.o main.cpp
	g++ -Wall main.cpp Combinator.o -std=gnu++11 -static-libstdc++ -o Combinator-teamSorenHolm

Combinator.o: Combinator.cpp Combinator.hpp
	g++ Combinator.cpp -Wall -c -std=gnu++11 -static-libstdc++
