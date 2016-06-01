CC = g++
HEADER_PATH = headers
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

_OBJ  = Main.o Game.o Camera.o State.o Sprite.o Vec2.o Rect.o TileSet.o TileMap.o
_OBJ += Resources.o InputManager.o Timer.o Animation.o Music.o Sound.o Text.o
_OBJ += LevelMap.o IntroState.o ProceduralMap.o ProceduralState.o AnimationFSM.o
_OBJ += Eva.o
OBJ = $(patsubst %,$(BIN_PATH)/%,$(_OBJ))

DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.Td
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

FINAL_EXEC = Project-M.K.Eva
all: $(FINAL_EXEC)
$(FINAL_EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BIN_PATH) $(DEP_PATH)
	$(CC) $(DEPFLAGS) -c -o $@ $< $(DIRECTIVES)
	@mv -f $(DEP_PATH)/$*.Td $(DEP_PATH)/$*.d

debug: DIRECTIVES += -ggdb
debug: CC = clang++
debug: all

release: DIRECTIVES += -Ofast -mtune=native
release: all

doc: 
	@doxygen Doxyfile

.PHONY: clean
clean:
	-@rm -r $(BIN_PATH) $(DEP_PATH) def/ html/ latex/ map/procedural_generated_map* $(FINAL_EXEC) 2>/dev/null || true

$(DEP_PATH)/%.d: ;
.PRECIOUS: $(DEP_PATH)/%.d

-include $(patsubst %,$(DEP_PATH)/%.d,$(basename $(_OBJ)))

