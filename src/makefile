CC = g++
IDIR = ../include
CFLAGS = -I$(IDIR)

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = GameLoop.cpp TextureManager.cpp

OUT = game.out

%.o: $.c
	$(CC) -c -o  $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS)

run:
	./$(OUT)
