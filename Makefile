CC=gcc
CFLAGS=-Iinclude -Wall -ansi

all: build_dir test

build_dir:
	mkdir -p build

test: src/cross_correlation.c tests/test.c
	$(CC) $(CFLAGS) src/cross_correlation.c tests/test.c -o build/test

clean:
	rm -rf build/*