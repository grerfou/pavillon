CC = g++
CFLAGS =  -Wall -std=c++11
#LDFLAGS = -L/usr/local/lib -lraylib -framework Cocoa -framework -lGL -lm -lpthread -ldl -lX11
LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

SOURCES = ./src/main.cpp ./src/displacement.cpp ./src/binary_conversion.cpp ./src/scene.cpp
OBJECT = $(SOURCES:.cpp=.o)
EXE = one_idea

.PHONY: all clean

all : $(EXE)

$(EXE) : $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

#clean :
#	$(RM) -f $(EXE) $(OBJECT)

clean :
	$(RM) -f $(OBJECT)



run : 
	make
	./one_idea
	make clean
