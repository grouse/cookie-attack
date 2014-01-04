OBJS = main.o engine.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = -lGL -lSDL2 $(DEBUG)


pong: $(OBJS)
	$(CC) $(LFLAGS) bin/main.o bin/engine.o -o pong

engine.o: src/engine.cpp src/engine.h
	$(CC) src/engine.cpp $(CFLAGS) -o bin/engine.o

main.o: src/main.cpp src/engine.h
	$(CC) src/main.cpp $(CFLAGS) -o bin/main.o
