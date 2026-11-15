CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic
SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
SDL_LIBS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)

EXEC = game
EXEC_CONSOLE = game_console
TEST = test_des
TEST_GFX = test_graphics

OBJ = main.o game.o des.o graphics.o inputs.o
OBJ_CONSOLE = main_console.o game.o des.o
OBJ_TEST = test_des.o game.o des.o
OBJ_GFX = test_graphique.o graphics.o game.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(SDL_LIBS)

$(EXEC_CONSOLE): $(OBJ_CONSOLE)
	$(CC) -o $@ $(OBJ_CONSOLE)

$(TEST): $(OBJ_TEST)
	$(CC) -o $@ $(OBJ_TEST)

$(TEST_GFX): $(OBJ_GFX)
	$(CC) -o $@ $(OBJ_GFX) $(SDL_LIBS)

main.o: main.c des.h graphics.h inputs.h game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c main.c

main_console.o: main_console.c des.h game.h
	$(CC) $(CFLAGS) -c main_console.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

des.o: des.c des.h game.h
	$(CC) $(CFLAGS) -c des.c

graphics.o: graphics.c graphics.h inputs.h des.h game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c graphics.c

inputs.o: inputs.c inputs.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c inputs.c

test_des.o: test_des.c des.h game.h
	$(CC) $(CFLAGS) -c test_des.c

test_graphique.o: test_graphique.c graphics.h game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c test_graphique.c

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC) $(EXEC_CONSOLE) $(TEST) $(TEST_GFX)