/*Might have made life eaier to do a linked list of structs*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define NAME_BUFFER 40
#define INIT_NAMES 10

typedef struct pair {
    char* name;
    char* giftee;
    char* hashed;
}Pair_t;

void add_names(char**, int*);
void display_list(char**, int*);
void sort_list(char**, int*);
char* hash_func(char*);


int main(int argc, char* argv[]) {

char** names = malloc(sizeof(char*)*INIT_NAMES);
    if (names == NULL) {
        printf("List malloc failed\n");
        exit(1);
    }
int * plist_size = malloc(sizeof(int*));
    if (plist_size == NULL) {
        printf("int pointer failed\n");
        exit(1);
    }
*plist_size = 0;
int run = 1;
int run_count = 0;
// TODO: deal with fgets overflow, etc
  while (run) {
    printf("Hello, which operation would you like to complete?\n");
    printf("A. Add names to the list\nB. Sort the list\n");
    printf("C. Decode recipient\nD. Display list of names\nE. Exit\n->");
    char choice[6];
    fgets(choice,6,stdin);
    // switch should handle most error checking for fgets
    strtok(choice,"\n");
    switch (choice[0]) {
      case 'A':
      case 'a': add_names(names, plist_size);
        break;
      case 'B':
      case 'b': sort_list(names,plist_size);
        break;
      case 'C':
      case 'c': printf("at c\n");//decode();
        break;
      case 'D':
      case 'd':display_list(names,plist_size);
        break;
      case 'E':
      case 'e': run = 0;
        break;
      default:
        printf("Didn't understand that. Please input a single character.\n");
    }

    run_count++;
    if (run_count > 10) {
      run = 0;
    } else if (run_count > 20) {
      char* msg = "broken loop";
      write(STDERR_FILENO, msg, strlen(msg));
      exit(1);
    }
  }

  printf("Goodbye!\n");
  return(0);
}

// TODO: deal with fgets overflow, etc
void add_names(char** list, int* plist_size) {
    int run = 1;
    while (run) {
        int curr = *plist_size;
        if (((curr % 10) == 0) && (curr != 0)) {
            list = realloc(list, sizeof(list) + sizeof(char*)*INIT_NAMES);
            if (list == NULL) {
                printf("realloc failed\n");
                exit(1);
            }
        }
        printf("Please add a name, or 'exit' to finish:\n");
        char name[NAME_BUFFER];
        fgets(name,NAME_BUFFER,stdin);
        strtok(name, "\n");
        // no need to check for duplicates since this is a one-time use program
        //and if things go wrong I will be there to run it again if needed
        if (strcmp(name, "exit") == 0) {
            run = 0;
        } else {
            list[curr] = malloc(strlen(name) + 1);
                if (list[curr] == NULL) {
                    printf("malloc failed for name\n");
                    exit(1);
                }
            strcpy(list[curr], name);
            *plist_size += 1;
        }
    }
}

void display_list(char** list, int* psize) {
    int length = *psize;
    int i;
    for (i = 0; i < length; i++) {
        printf("%s\n",list[i]);
    }
    printf("\n");
}

void sort_list(char ** list, int * psize) {
    // assign each list name to a pair struct
    int size = *psize;
    Pair_t* structs = malloc(size * sizeof(Pair_t));
        if (structs == NULL) {
            printf("struct malloc failed");
            exit(1);
        }
    int i;
    for (i = 0; i < size; i++) {
        structs[i].name = list[i];
    }
    // assign the pairings
    int nums[size];
    int r;
    int j;
    int unique;
    for (i = 0; i < size; i++) {
        do{
            unique = 1;
            r = rand() % size;
            for (j = 0; j < size; j++) {
                if (nums[j] == r) {
                    unique = 0;
                }
            }
        } while (!unique);
        nums[i] = r;
    }
    // have random numbers for each one, now assign giftees
    for (i = 0; i < size; i++) {
        structs[i].giftee = list[nums[i]];
        //hash the name
        structs[i].hashed = hash_func(structs[i].giftee);
        //printf("%s--> %s\n", structs[i].name, structs[i].hashed);
    }
    // display pairings

}


char* hash_func(char* name) {
    int length = strlen(name);
    char arr[2*length];
    int i;
    //add rand numbers in all the other spots
    int j = 0;
    for (i = 1; i < (2*length); i+=2) {
        arr[i] = name[j];
        j++;
    }
    for (i = 0; i < (2*length); i+=2) {
        arr[i] = (rand() % 7) + '0';
    }
    printf("%s\n",arr );
    return strdup(arr);
}
