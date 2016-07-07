OS = linux

CFLAGS = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)
HEADER_PATH = headers
SRC_PATH = src
DEP_PATH = dep

ifeq ($(OS), linux)
	CC = g++
	BIN_PATH = bin
	LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
	FINAL_EXEC = Project-M.K.Eva
else
	PREFIX = /usr/local/cross-tools/
	TOOLSET = x86_64-w64-mingw32
	CROSSPATH = $(PREFIX)/$(TOOLSET)
	PKG_CONFIG_PATH = ${CROSSPATH}/lib/pkgconfig
	PATH += ${CROSSPATH}/bin

	CC = $(TOOLSET)-g++ -static-libgcc -static-libstdc++
	BIN_PATH = wbin
	CFLAGS += -I $(CROSSPATH)/include -D WINDOWS 
	LDFLAGS = `$(CROSSPATH)/bin/sdl2-config --libs` -lSDL2_image.dll
	LDFLAGS += -lSDL2_ttf.dll -lSDL2_mixer.dll -L${CROSSPATH}/lib/ -lpthread
	FINAL_EXEC = Project-M.K.Eva.exe
endif

_OBJ  = Main.o Game.o Camera.o State.o Sprite.o Vec2.o Rect.o TileSet.o
_OBJ += TileMap.o Resources.o InputManager.o Timer.o Animation.o Music.o Sound.o
_OBJ += Text.o LevelMap.o IntroState.o ProceduralMap.o ProceduralState.o
_OBJ += AnimationFSM.o Eva.o TurretMonster.o Bullet.o MekaBugMonster.o
_OBJ += TurretMobMonster.o BallMonster.o BallsManager.o Eva.o HubState.o
_OBJ += FirstLevelState.o ProceduralFirstRooms.o EvaClass.o EvaBase.o 
_OBJ += EvaDecker.o EvaGunslinger.o EvaSamurai.o Bullet.o AttackClass.o Room.o
_OBJ += HealthBar.o TitleState.o Monster.o Door.o
OBJ = $(patsubst %,$(BIN_PATH)/%,$(_OBJ))

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.Td

all: $(FINAL_EXEC)
$(FINAL_EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BIN_PATH) $(DEP_PATH)
	$(CC) $(DEPFLAGS) -c -o $@ $< $(CFLAGS)
	@mv -f $(DEP_PATH)/$*.Td $(DEP_PATH)/$*.d

debug: CFLAGS += -ggdb
debug: CC = clang++
debug: all

release: CFLAGS += -Ofast -mtune=native
release: all

.PHONY: doc
doc: 
	@doxygen Doxyfile

.PHONY: format
format:
	bash format.sh
	

.PHONY: clean
clean:
	-@rm -r $(BIN_PATH) w$(BIN_PATH) $(DEP_PATH) def/ html/ latex/ map/procedural_generated_map* tilemap/procedural_generated_* $(FINAL_EXEC) 2>/dev/null || true

$(DEP_PATH)/%.d: ;
.PRECIOUS: $(DEP_PATH)/%.d

-include $(patsubst %,$(DEP_PATH)/%.d,$(basename $(_OBJ)))

