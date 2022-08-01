CC := gcc

all:
	$(CC) src/*.c libraylib.a -lglfw -lrt -lm -ldl -pthread -o stuge
