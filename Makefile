CC=gcc
CFLAGS=-Iinclude -Wall -ansi -O3

all: build_dir test_suite

build_dir:
	mkdir -p build sinais saidas_c saidas_py

test_suite: src/cross_correlation.c tests/test_suite.c
	$(CC) $(CFLAGS) src/cross_correlation.c tests/test_suite.c -o build/test_suite -lm

clean:
	rm -rf build/* sinais saidas_c saidas_py