pong: main.o
	g++ -lSDL2 bin/main.o -o pong

main.o: src/main.cpp
	g++ src/main.cpp -c -o bin/main.o
