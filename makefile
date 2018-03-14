CC = gcc
C_FLAGS = -lm
HEADERS = -i/include

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: build

build: clean
	$(CC) $(C_FLAGS)
clean:
	rm -f /bin/*