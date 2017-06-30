CC = g++
IDIR = ../include
ISFML = ../SFML/include
LSFML = ../SFML/lib
CFLAGS = -std=c++14 -I$(IDIR)

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = GameLoop.cpp Game.cpp TextureManager.cpp Level.cpp Hero.cpp

OUT = game.out

%.o: $.c
	$(CC) -c -o  $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS)

run:
	LD_LIBRARY_PATH="../SFML/lib:$LD_LIBRARY_PATH" ./$(OUT)
