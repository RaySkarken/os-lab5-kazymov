#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE * output_file;
    char symbol;
    const int ctrl_f_code = 6;
    const char end_symbol = ctrl_f_code;  // ctrl+f
    if (argc!=2) {
        printf("ERROR! output file name where not provided!\n");
        return 1;
    }
    if((output_file=fopen(argv[1], "w")) == NULL) {
        printf("ERROR! File can't be opened!\n");
    return 1;
        }
    symbol = getc(stdin);
    while (symbol!=end_symbol) {
        putc(symbol, output_file);
        symbol = getc(stdin);
    }
    fclose(output_file);
    return 0;
}
