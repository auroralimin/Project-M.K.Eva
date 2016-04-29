CC = g++

SDIR = src
HDIR = headers
ODIR = obj

_OBJ = Main.o Game.o Camera.o State.o Sprite.o Vec2.o Rect.o Face.o TileSet.o
_OBJ += TileMap.o Resources.o InputManager.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CFLAGS = -I$(HDIR) -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lSDL2_image -lm

all: 130006408_T4

debug: CFLAGS += -g
debug: all

$(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

130006408_T4: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	-rm -r $(ODIR) 130006408_T*

