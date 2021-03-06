/** 
 * This is purely a learning exercise in C programming.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * Checks whether the two numbers match. Prints a message and returns false if
 * they don't match. Returns true if they do match.
 */
bool check_num(int rand_num, int guess_num) {
  if (guess_num < rand_num) {
    printf("Your guess is too low.\n");
    return false;
  } else if (guess_num > rand_num) {
    printf("Your guess is too high.\n");
    return false;
  } else {
    return true;
  }
}

/**
 * Seeds the random number generator and then returns a random number from 1 and
 * the maximum number specified.
 */
int gen_num(int max) {
  srand(time(NULL));
  return rand() % max + 1;
}

/**
 * Parses a number from the given character array.
 */
int parse_num(char value[]) {
  int num = 0;

  if (sscanf(value, "%d", &num) != 1) {
    printf("That didn't work... Try using a valid number greater than 0.\n");
  }
  return num;
}

/**
 * Asks for a number. Since we're only concerned with numbers greater than 0, we
 * return 0 in the event that there was an error.
 */
int ask_num(char prompt[]) {
  int num = 0;
  char input[100];

  while (num <= 0) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) != NULL) {
      num = parse_num(input);
    }
  }
  return num;
}

/**
 * Print usage information
 */
void usage() {
  printf("Usage: guessing_game [-m number] [-M number]\n");
  printf("\t-m number\tSpecify the maximum possible number.\n");
  printf("\t-M number\tSpecify the maximum number of tries.\n");
}

/**
 * Main function
 */
int main(int argc, char *argv[]) {
  int rand_num = 0,     // The random number we're generating.
      guess_num = 0,    // The user's current guess.
      counter = 0,      // The counter (keeping track of how many times the user guessed).
      max = 0,          // Maximum bound for random numbers.
      max_tries = 0,    // The maximum amount of tries (if set).
      c = 0;            // Used for getopt.
  bool correct = false; // Tracks whether the user made a correct guess.

  while ((c = getopt(argc, argv, "hm:M:")) != -1) {
    switch (c) {
    case 'h':
      usage();
      return 0;
    case 'm':
      max = parse_num(optarg);

      if (max == 0) {
        usage();
        return 1;
      }
      break;
    case 'M':
      max_tries = parse_num(optarg);

      if (max_tries == 0) {
        usage();
        return 1;
      }
      break;
    }
  }
  if (max == 0) {
    max = ask_num("Enter a maximum number (must be a positive number):\n> ");
  }
  rand_num = gen_num(max);

  while (!correct) {
    counter++;

    if (max_tries > 0 && max_tries < counter) {
      printf("You guessed wrong too many times. Try again!\n");
      return 0;
    }
    guess_num = ask_num("Guess the number:\n> ");
    correct = check_num(rand_num, guess_num);
  }
  printf("You guessed the correct number in %d tries!\n", counter);
  return 0;
}
