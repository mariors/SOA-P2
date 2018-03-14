CC = gcc
MK_DIR = mkdir
HEADERS = -Iinclude/
C_FLAGS = -Wall -lm -Os $(HEADERS)

SRC_DIR = src
BIN_DIR = bin

MAIN_FILE = project.o

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(BIN_DIR)/$(MAIN_FILE)

build: compile
	@echo DONE!
	@echo Compilation done. Set args, if needed, in projects\'s "etc" folder 
	@echo and then run with: ./$(OBJ)
compile: clean
	@echo COMPILING...
	$(MK_DIR) $(BIN_DIR)
	$(CC) $(SRC) $(C_FLAGS) -o $(OBJ)
clean:
	@echo CLEANING STEP!
	$(RM) -rf $(BIN_DIR)/*.o $(BIN_DIR)