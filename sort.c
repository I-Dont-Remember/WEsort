#include <stdio.h>



int main(int argc, char* argv[]) {

// menu prompt
int run = 1;
int run_count = 0;
  while (run) {
    printf("Hello, which operation would you like to complete?\n");
    printf("A. Add names to the list\nB. Sort the list\n");
    printf("C. Decode recipient\nD. Exit");

    //input choice
    scanf("%c",choice); // placeholder, use fgets and strtok(buffer,"\n")
    switch (choice) {
      case 'A':
      case 'a': add_names();
        break;
      case 'B':
      case 'b': sort_list();
        break;
      case 'C':
      case 'c': decode();
        break;
      case 'D':
      case 'd':
        run = 0;
        break;
      default:
        printf("Didn't understand that"); 
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

  printf("Goodbye!");
  return(0);
}


