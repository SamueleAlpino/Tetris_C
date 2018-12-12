CC=clang
CPPCHECK=cppcheck
CFLAGS= -Wall -Werror -O3 -I D:\Sam\tetris_c\SDL2\include -Wno-pragma-pack
LDFLAGS=-lSDL2 
BINARY=tetris
BINARY_TESTS=tetris_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

tetris: main.o tetris.o gfx.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^

tetris.o: tetris.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<

gfx.o: gfx.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^

test: tests.o tetris.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o tetris