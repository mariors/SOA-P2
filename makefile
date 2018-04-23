CC = gcc
MK_DIR = mkdir
HEADERS = -Iinclude/
LIBS_FOLDER_FLAG = -Llib/
LIBS_FLAG = 

C_FLAGS = -Wall -lm -Os -lrt -pthread $(HEADERS) \
	$(LIBS_FOLDER_FLAG) \
	$(LIBS_FLAG)

SRC_DIR = src
BIN_DIR = bin

MAIN_FILE = project.o

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_GLOBAL = $(wildcard $(SRC_DIR)/global/*.c)
SRC_GLOBAL1 = $(wildcard $(SRC_DIR)/global/**/*.c)
SRC_GLOBAL2 = $(wildcard $(SRC_DIR)/global/**/**/*.c)

FULL_SRC = $(SRC_GLOBAL) $(SRC_GLOBAL1) $(SRC_GLOBAL2)

OBJ = $(BIN_DIR)/$(MAIN_FILE)


SRC_CREATOR = $(wildcard $(SRC_DIR)/creator/creator.c)


SRC_PRODUCER = $(wildcard $(SRC_DIR)/consumer/consumer.c)


SRC_CONSUMER = $(wildcard $(SRC_DIR)/producer/producer.c)


SRC_TERMINATOR = $(wildcard $(SRC_DIR)/creator/creator.c)


build: compile
	@echo DONE!
	@echo Compilation done. Set args, if needed, in projects\'s "etc" folder 
	@echo and then run with: ./$(OBJ)
compile: clean
	@echo COMPILING...
	$(CC) $(SRC) $(C_FLAGS) -o $(OBJ)
creator: creator
	$(CC) $(FULL_SRC) $(SRC_CREATOR) $(C_FLAGS) -o bin/creator.o
consumer: consumer
	$(CC) $(FULL_SRC) $(SRC_PRODUCER) $(C_FLAGS) -o bin/consumer.o
producer: producer
	$(CC) $(FULL_SRC) $(SRC_CONSUMER) $(C_FLAGS) -o bin/producer.o
clean:
	@echo CLEANING STEP!
	$(RM) -rf $(BIN_DIR)/*.o $(BIN_DIR)
	$(MK_DIR) $(BIN_DIR)