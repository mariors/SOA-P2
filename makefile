CC = gcc
MK_DIR = mkdir
HEADERS = -I/include
C_FLAGS = -Wall -lm -Os $(HEADERS)

SRC_DIR = src
BIN_DIR = bin

MAIN_FILE = main.o

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

all: build
	@echo Compilation done. Set args, if needed, in projects's "etc" folder and run: ./$(BIN_DIR)/$(MAIN_FILE)
build: clean
	$(MK_DIR) $(BIN_DIR)
	$(CC) $(SRC) $(C_FLAGS) -o $(OBJ)
clean:
	$(RM) -f $(BIN_DIR)/*.o $(BIN_DIR)/*~