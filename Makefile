CC=gcc
CFLAGS=-Iinclude -Wall -ansi

all: build_dir test_impulso test_atraso

build_dir:
	mkdir -p build

test_impulso: src/cross_correlation.c tests/test_impulso.c
	$(CC) $(CFLAGS) src/cross_correlation.c tests/test_impulso.c -o build/test_impulso

test_atraso: src/cross_correlation.c tests/test_atraso.c
	$(CC) $(CFLAGS) src/cross_correlation.c tests/test_atraso.c -o build/test_atraso

clean:
	rm -rf build/*