#include "kevin.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Gets user input from keyboard, consumes excess if needed
@return: if empty or only white space, returns EMPTY or JUST_SPACES
*/
char* getusrinput(int buff_size) {
    char buffer[buff_size];
    fgets(buffer, buff_size, stdin);
    // excess input consumption
    if (strchr(buffer,'\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n');
    }
    // check if empty
    if (strcmp(buffer,"\n") == 0) {
        return "EMPTY";
    }
    // check just white spaces
    int len = strlen(buffer);
    int k;
    int spaces = 1;
    for (k = 0; k < len; k++) {
        // returns 0 if not whitespace
        if((isspace(buffer[k])) == 0) {
            spaces = 0;
        }
    }

    if(spaces) {
        return "JUST_SPACES";
    } else {
        // clean of fgets newline
        strtok(buffer,"\n");
        return strdup(buffer);
    }
}
