CC = cc
OUT = guessing_game

$(OUT): guessing_game.c
	$(CC) -pedantic -O3 -o $(OUT) guessing_game.c

clean:
	rm $(OUT)
