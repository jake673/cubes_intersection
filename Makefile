TARGET = main
OBJECTS = main.o Cube.o Geometry.o 
SRCDIR = ./
CC = g++
CFLAGS = -std=c++14 -Wall -O2 -I/opt/homebrew/Cellar/glm/1.0.1/include

default: $(TARGET)
all: default

$(TARGET): $(OBJECTS)
	$(CC) $^ -Wall -o $@
	
%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	-rm -f *.o
	-rm -f $(TARGET)	
