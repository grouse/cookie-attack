OBJS = main.o engine.o rect.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = -lGL -lSDL2 $(DEBUG)


pong: $(OBJS)
	$(CC) $(LFLAGS) bin/main.o bin/engine.o bin/rect.o -o pong

engine.o: src/engine.cpp src/engine.h
	$(CC) src/engine.cpp $(CFLAGS) -o bin/engine.o

rect.o: src/rect.cpp src/rect.h
	$(CC) src/rect.cpp $(CFLAGS) -o bin/rect.o

main.o: src/main.cpp src/engine.h
	$(CC) src/main.cpp $(CFLAGS) -o bin/main.o

engine.h: src/rect.h
