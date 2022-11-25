#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE * input_file;
    int n;
    int printed_lines_count = 0;
    char symbol;
    if (!sscanf(argv[2], "%d", &n)) {
        printf("ERROR! Length of group must be a number!\n", n);
        return 1;
    }
    if (n < 0) {
        printf("ERROR! Length of group must be a non-negative integer!\n");
        return 1;
    }
    if (argc<3) {
        printf("ERROR! Too few arguments!\n");
        return 1;
    }
    if (argc>3) {
        printf("ERROR! Too many arguments!\n");
        return 1;
    }
    if((input_file=fopen(argv[1], "r")) == NULL) {
        printf("ERROR! File can't be opened!\n");
        return 1;
    }
    
    symbol = getc(input_file);
    while (symbol!=EOF) {
        putc(symbol, stdout);
        if (symbol == '\n') printed_lines_count++;
        if (n > 0 && printed_lines_count == n) {
            getc(stdin);
            printed_lines_count = 0;
        }
        symbol = getc(input_file);
    }
    fclose(input_file);
    return 0;
}
