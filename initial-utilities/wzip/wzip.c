#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    FILE *fp;
    char last_char = 0;
    int counter = 0;
    char ch;

    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while ((ch = fgetc(fp)) != EOF) {
            if (ch != last_char && counter != 0) {
                fwrite(&counter, sizeof(int), 1, stdout);
                fputc(last_char, stdout);
                last_char = ch;
                counter = 0;
            } else if (counter == 0) {
                last_char = ch;
            }
            counter++;
        }

        fclose(fp);
    }

    if (counter > 0) {
        fwrite(&counter, sizeof(int), 1, stdout);
        fputc(last_char, stdout);
    }

    return EXIT_SUCCESS;
}
