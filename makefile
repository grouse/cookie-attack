CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

CC = g++
DEBUG = -g
CFLAGS = -c -MMD $(DEBUG)
LFLAGS = -lGL -lSDL2 $(DEBUG)

pong: $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

-include $(OBJ_FILES:.o=.d)
