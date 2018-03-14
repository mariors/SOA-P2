CC = gcc
HEADERS = -I/include
C_FLAGS = -Wall -lm $(HEADERS)

SRC_DIR = src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

all: build

build: clean
	$(CC) $(SRC) $(C_FLAGS) -o $(OBJ)
clean:
	rm -f $(BIN_DIR)/*