/** 
 * This is purely a learning exercise in C programming.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool check_num(int rand_num, int guess_num) {
	if (guess_num < rand_num) {
		printf("Your guess is too low. Guess again!\n");
		return false;
	} else if (guess_num > rand_num) {
		printf("Your guess is too high. Guess again!\n");
		return false;
	} else {
		return true;
	}
}

int gen_num(int max) {
	srand(time(NULL));
	return rand() % max + 1;
}

int ask_num(char prompt[]) {
	int num = 0;
	char input[100];

	while (num <= 0) {
		printf("%s", prompt);
		fflush(stdout);

		if (fgets(input, sizeof input, stdin) != NULL) {
			if (sscanf(input, "%d", &num) != 1) {
				num = 0;
				printf("That didn't work...\n");
			}
		}
	}
	return num;
}

int main(void) {
	int rand_num = 0;
	int guess_num = 0;
	int counter = 0;
	int max = 0;
	bool correct = false;

	max = ask_num("Enter a maximum number (must be a positive number):\n> ");
	rand_num = gen_num(max);

	while (!correct) {
		counter++;
		guess_num = ask_num("Guess the number:\n> ");
		correct = check_num(rand_num, guess_num);
	}
	printf("You guessed the correct number in %d tries!\n", counter);
	return 0;
}
