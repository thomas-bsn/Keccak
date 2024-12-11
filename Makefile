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

test1: clean keccak # On compare les hash du fichier entre le binaire C et le binaire Python
	@echo "===== On compare les hash =====" 
	@python3 test/test.py

test2: clean keccak # On compare le premier bloc du fichier test entre le binaire C et le binaire Python
	@echo "===== On compare le premier bloc ====="
	@python3 test/compare_blocks.py

test3: clean keccak # Print le hash d'un state rempli de 0 par la binaire Python, a tester manuellement avec le code source en C avec la macro TEST = 1
	@echo "===== Print le hash d'un state rempli de 0 ====="
	@python3 test/squeeze.py

clean:
	rm -f $(TARGET)
	rm -f test/*.txt
