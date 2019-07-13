CC := gcc
CFLAGS := -W -Wall
LDFLAGS := -lallegro -lallegro_image

# folders
BIN_PATH := bin
SRC_PATH := src

BIN_NAME := Galaga
SOURCES=$(wildcard $(SRC_PATH)/*.c)

all: galaga 
 
galaga: $(SOURCES)
	$(CC) -o $(BIN_PATH)/$(BIN_NAME) $(LDFLAGS) $(SOURCES)
 
