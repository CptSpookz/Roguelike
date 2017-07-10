CC = g++.exe
IDIR = ../include
ISFML = ../SFML/include
LSFML = ../SFML/lib
CFLAGS = -I$(IDIR) -I$(ISFML) -L$(LSFML) -std=c++14 -mwindows

LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

OBJ = GameLoop.cpp Game.cpp TextureManager.cpp Level.cpp Hero.cpp Char.cpp Object.cpp ButtonList.cpp Enemy.cpp Projectile.cpp Potion.cpp

OUT = ../bin/randventure.exe

%.o: $.c
	$(CC) -c -o  $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS)

run:
	LD_LIBRARY_PATH="../bin" ./$(OUT)
