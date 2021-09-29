#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <byteswap.h>


#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


int main(int argc, char *argv[]) {
    FILE *fp;
    size_t ret; 
    int j;
    unsigned char buffer[1];

    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        // while not EOF
        // read first 4 bytes and print its ASCII representation
        // then read 1 byte and print its ASCII representation
        while ((ret = fread(&j, sizeof(int), 1, fp)) == 1) {
            fread(buffer, sizeof(char), sizeof(char), fp);
            for (;j > 0; j--) {
                printf("%c", buffer[0]);
            }
        }
    }


    return EXIT_SUCCESS;
}
