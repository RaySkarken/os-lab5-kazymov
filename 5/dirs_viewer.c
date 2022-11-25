#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR * dp, * dp2;
    struct dirent * d;

    if ( ( dp = opendir(".") ) == NULL ) {
        printf("ERROR! Current directory is forbidden\n");
        return 1;
    }
    if ((dp2 = opendir(argv[1])) == NULL) {
        printf("ERROR! Current directory is forbidden\n");
        return 1;
    }
    if (argc<2) {
        printf("ERROR! Too few arguments!\n");
        return 1;
    }
    if (argc>2) {
        printf("ERROR! Too many arguments!\n");
        return 1;
    }
    printf("(current directory):\n");
    d = readdir(dp);
    while ( d != NULL ) {
        printf("    %s\n", d->d_name);
        d = readdir(dp);
    }
    printf("%s:\n", argv[1]);
    d = readdir(dp2);
    while ( d != NULL ) { 
        printf("    %s\n", d->d_name);
        d = readdir(dp2);
    }

    closedir(dp);
    closedir(dp2);
    return 0;
}
