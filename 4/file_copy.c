#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE * input_file, * output_file;
    char symbol;
    if (argc<3) {
        printf("ERROR! Too few arguments!\n");
        return 1;
    }
    if (argc>3) {
        printf("ERROR! Too many arguments!\n");
        return 1;
    }
    if((input_file=fopen(argv[1], "r")) == NULL) {
        printf("ERROR! Source file can't be opened!\n");
        return 1;
    }
    if((output_file=fopen(argv[2], "w")) == NULL) {
        printf("ERROR! Destination file can't be opened!\n");
        return 1;
    }

    symbol = getc(input_file);
    while (symbol!=EOF) {
        putc(symbol, output_file);
        symbol = getc(input_file);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
