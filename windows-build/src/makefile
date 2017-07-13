CC = g++.exe
IDIR = ../include
LMINGW = C/dev/msys64/mingw64/x86_64-w64-mingw32/lib
ISFML = ../SFML/include
LSFML = ../SFML/lib
CFLAGS = -DSFML_STATIC -I$(IDIR) -I$(ISFML) -L$(LMINGW) -L$(LSFML) -std=c++14 -mwindows

LIBS = -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lfreetype -ljpeg -lopengl32 -lgdi32 -lwinmm

OBJ = GameLoop.cpp Game.cpp TextureManager.cpp Level.cpp Hero.cpp Char.cpp Object.cpp ButtonList.cpp Enemy.cpp Projectile.cpp Potion.cpp

OUT = ../bin/randventure.exe

%.o: $.c
	$(CC) -c -o  $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS)

run:
	LD_LIBRARY_PATH="../bin" ./$(OUT)
