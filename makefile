OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = -lSDL2 $(DEBUG)


pong: $(OBJS)
	$(CC) $(LFLAGS) bin/main.o -o pong

main.o: src/main.cpp
	$(CC) src/main.cpp $(CFLAGS) -o bin/main.o
