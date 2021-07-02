CC = gcc
CFLAGS = -Wall

test:
	gcc -g src/printer.c src/types.c src/reader.c tests/test_reader.c -o tr
	gcc -g src/env.c src/types.c tests/test_env.c -o te

build:
	gcc -g src/env.c src/printer.c src/main.c src/types.c src/reader.c -o lsip