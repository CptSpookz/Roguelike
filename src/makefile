CC = g++
IDIR = ../include
ISFML = ../SFML/include
LSFML = ../SFML/lib
CFLAGS = -I$(IDIR) -I$(ISFML) -L$(LSFML) -std=c++14

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = GameLoop.cpp Game.cpp TextureManager.cpp

OUT = game.out

%.o: $.c
	$(CC) -c -o  $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS)

run:
	LD_LIBRARY_PATH="../SFML/lib:$LD_LIBRARY_PATH" ./$(OUT)
