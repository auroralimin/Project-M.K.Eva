CC = g++
HEADER_PATH = headers
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

_OBJ = Main.o Game.o Camera.o State.o Sprite.o Vec2.o Rect.o Face.o TileSet.o
_OBJ += TileMap.o Resources.o InputManager.o Alien.o Minion.o Bullet.o
OBJ = $(patsubst %,$(BIN_PATH)/%,$(_OBJ))

DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.Td
LIBS = -lSDL2 -lSDL2_image -lm

FINAL_EXEC = 130006408_T5
all: $(FINAL_EXEC)
$(FINAL_EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BIN_PATH) $(DEP_PATH)
	$(CC) $(DEPFLAGS) -c -o $@ $< $(DIRECTIVES)
	@mv -f $(DEP_PATH)/$*.Td $(DEP_PATH)/$*.d

debug: DIRECTIVES += -ggdb
debug: all

.PHONY: clean
clean:
	-@rm -r $(BIN_PATH) $(DEP_PATH) 130006408_T* 2>/dev/null || true

$(DEP_PATH)/%.d: ;
.PRECIOUS: $(DEP_PATH)/%.d

-include $(patsubst %,$(DEP_PATH)/%.d,$(basename $(_OBJ)))

