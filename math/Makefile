TARGET = src/main.cpp src/player.cpp src/wall.cpp src/sector.cpp

BIN = bin/main

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all:
	g++ $(TARGET) -o $(BIN) $(LIBS)
	./bin/main

run:
	./bin/main

compile:
	g++ $(TARGET) -o $(BIN) $(LIBS)
