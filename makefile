CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

CC = g++
DEBUG = -g -Wall
CFLAGS = -c -std=c++11 -MMD $(DEBUG)
LFLAGS = -lGL -lSDL2 $(DEBUG)

cookie-attack: $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

-include $(OBJ_FILES:.o=.d)
