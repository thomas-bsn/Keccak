CC = gcc

CFLAGS = -Wall -Wextra -O2 -std=c11 -Iinclude

SRC_DIR = src
STEP_DIR = src/step
INCLUDE_DIR = include

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/keccak.c $(SRC_DIR)/utils.c \
            $(STEP_DIR)/bloc_part.c $(STEP_DIR)/absorption.c $(STEP_DIR)/permut.c \
            $(STEP_DIR)/squeeze.c

TARGET = keccak

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC_FILES) -o $@

test: keccak
	python3 test/test.py

clean:
	rm -f $(TARGET)
