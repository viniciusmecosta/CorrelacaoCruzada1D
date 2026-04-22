CC=gcc
CFLAGS=-Iinclude -Wall -ansi -O2

all: build_dir test_suite

build_dir:
	mkdir -p build

test_suite: src/cross_correlation.c tests/test_suite.c
	$(CC) $(CFLAGS) src/cross_correlation.c tests/test_suite.c -o build/test_suite

clean:
	rm -rf build/*