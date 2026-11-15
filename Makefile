CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic
EXEC = game
TEST = test_des
OBJ = main.o game.o des.o
OBJ_TEST = test_des.o game.o des.o
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
EXEC = game
SRC = game.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ)

$(TEST): $(OBJ_TEST)
	$(CC) -o $@ $(OBJ_TEST)

main.o: main.c des.h game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

des.o: des.c des.h game.h
	$(CC) $(CFLAGS) -c des.c

test_des.o: test_des.c des.h game.h
	$(CC) $(CFLAGS) -c test_des.c

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC) $(TEST)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) $(EXEC).exe

.PHONY: all clean mrproper
