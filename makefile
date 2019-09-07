CC = gcc
CFLAGS = -W -Wall
LDFLAGS = -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include

# Windows Only
# Path to Allegro headers
ALLEGRO_INCLUDE_PATH = allegro/include
# Path to Allegro monolith library
ALLEGRO_MONOLITH_PATH = $(ALLEGRO_INCLUDE_PATH:include=lib/liballegro-5.0.10-monolith-mt.a)

EXE = GalaxyDefenders
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

all: $(EXE)
 
$(EXE): $(OBJ)
ifeq ($(OS),Windows_NT)
	@if not exist "$(BIN_DIR)" mkdir $(BIN_DIR)
	$(CC) -mwindows -o $(BIN_DIR)/$@ $(OBJ) $(ALLEGRO_MONOLITH_PATH)
else
	mkdir -p $(BIN_DIR)
	$(CC) -I$(INC_DIR) $(LDFLAGS) -o $(BIN_DIR)/$@ $(OBJ)
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS),Windows_NT)
	@if not exist "$(OBJ_DIR)" mkdir $(OBJ_DIR)
	$(CC) -I$(INC_DIR) -I $(ALLEGRO_INCLUDE_PATH) $(CFLAGS) -c $< -o $@
else
	mkdir -p $(OBJ_DIR)
	$(CC) -I$(INC_DIR) $(CFLAGS) -c $< -o $@
endif

clean:
	$(RM) $(OBJ)

.PHONY: all clean
