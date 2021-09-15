#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512


int main(int argc, char *argv[]) {

    FILE *fp;
    char *lineptr = NULL;
    char *needle = argv[1];
    size_t len = 0;

    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
      char buffer[BUFFER_SIZE];
      while(fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
          if (strstr(buffer, needle) != NULL) {
              printf("%s", buffer);
          }
      }
    } else {
        for (int i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }

            while(getline(&lineptr, &len, fp) != -1) {
                if (strstr(lineptr, needle) != NULL) {
                    printf("%s", lineptr);
                }
            }

            free(lineptr);
            fclose(fp);
        }
    }

    exit(EXIT_SUCCESS);
}
