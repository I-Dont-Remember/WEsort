#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "kevin.h"

#define UPPER 65
#define LOWER 97
// shuffle array of structs until it works?
// OR shufffle integers until they don't match the index
// TODO make first version with limited number of names, can then expand
void add_names(int*, char**);
char** sort_list(char**, int*);
char* hash(char*);
void display_list();
void display_sorted();
int main(int argc, char* argv[]) {
  char** names;
  names = malloc(30 * sizeof(char*));
    if (names == NULL) {
      printf("names malloc failed");
      exit(1);
    }
  int* count = malloc(sizeof(int*));
  char** recipients;
    // menu prompt
    *count = 0;
    int run = 1;
    int no_choice = 0;
    while (run) {
    // get inital prompt input
      printf("What do you want to do?\nA. Add names\nB. Display current list\nC. sort list\nD. Display sorted list\nE. Exit and finish\n");
        char* input = getusrinput(25);
            // check input for problems
            if ((strcmp(input, "EMPTY") == 0) ||
                    (strcmp(input, "JUST_SPACES") == 0)) {
                no_choice = 1;
            }
    // switch to choose the different options in menu, if no choice loops
    if (!no_choice) {
        switch (input[0]) {
            case 'A':
            case 'a': add_names(count, names);
                break;
            case 'B':
            case 'b': display_list(names, count);
                break;
            case 'C':
            case 'c':recipients = sort_list(names, count);
                break;
            case 'D':
            case 'd': display_sorted(names, recipients, count);
                break;
            case 'E':
            case 'e': run = 0;
                break;
              default:
                printf("Didn't understand that.Please input a single character.\n");
        }
    }

    }
    printf("Goodbye!\n");
    return(0);
} // end of main

void add_names(int* count, char** names) {
  // doesn't handle more than initialized names, but that shouldn't matter for our uses
  int run = 1;
  int num = *count;
  if (num >= 30) {
    run = 0;
    printf("Names maxed out\n");
  }

  while (run) {
    printf("Add a name to the list, or \"done\" to return: ");
    char* input = getusrinput(40);
    int done = (strcmp(input, "done") == 0);
    int empty = (strcmp(input,"EMPTY") == 0);
    int spaces = (strcmp(input, "JUST_SPACES") == 0);
    // check for empty or whitespace
    if (done) {
      run = 0;
    } else if (empty || spaces) {
      printf("Please input a name.\n");
    } else {
      names[num] = malloc(strlen(input) * sizeof(char));
        if (names[num] == NULL) {
          printf("list name malloc failed");
          exit(1);
        }
      names[num] = input;
      num++;
    }
  }
  *count = num;
}

// TODO: check if giftees/recipients is actually initialized
char** sort_list(char** names, int* count) {
  if ((names == NULL) || (*count < 3)) {
    printf("Need names/enough names to sort.\n");
  } else {
    // allocate memory for giftees
    int num = *count;
    char** giftees = malloc(num * sizeof(char*));
      if (giftees == NULL) {
        printf("malloc failed, giftees");
        exit(1);
      }
    // get array to shufffle, nums 0 - (num -1)
    int ints[num], i, r, temp;
    for (i = 0; i < num; i++) {
      ints[i] = i;
    }
    srand(time(NULL));
    int valid = 0;
    while (!valid) {
      valid = 1;
      // Fisher yates algorithm to get int array
      // then check that no index matches its number i == int[i]
      for (i = (num-1); i > 0; i--) {
        r = rand() % i;
        temp = ints[i];
        ints[i] =  ints[r];
        ints[r] = temp;
      }
      // check if needs to reshuffle
      for (i = 0; i < num; i++) {
        if (i == ints[i]) {
          valid = 0;
        }
      }
    } // while
    // index of ints corresponds to index of giftees, int inside is rand index
    for(i = 0; i < num; i++) {
      giftees[i] = names[ints[i]];
    //  printf("%s --> %s\n",names[i], giftees[i]);
    }
    return giftees;
  }
}

void display_list(char** names, int* count) {
  if (*names == NULL) {
    printf("Need names to display\n");
  } else {
    printf("CURRENT NAMES:\n");
    int num = *count, i;
    for(i = 0; i < num; i++) {
      printf("%s\n", names[i]);
    }
  }
}

void display_sorted(char** names, char** giftees, int* count) {
  if ((*giftees == NULL) || (*count < 3)) {
    printf("Can't display empty list\n");
  } else {
    int num = *count, i;
    char* temp;
    for(i = 0; i < num; i++) {
      temp = hash(giftees[i]);
      printf("%s --> %s\n",names[i], temp);
    }
  }
}

char* hash(char* name) {
  // based on Caesar Cipher
  // TODO add something for spaces?
  char* temp = strdup(name);
  int cipher_num = 3, start, i;
  int len = strlen(temp);
  for (i = 0; i < len; i++) {
    // check if alpha, then check case
    if (isalpha(temp[i])) {
      if (isupper(temp[i])) {
        start = UPPER;
      } else {
        start = LOWER;
      }
      // get cipher index, then convert back to ascii
      int index = ((temp[i] - start) + cipher_num) % 26;
      temp[i] = start + index;
    }
  }
  return temp;
}
