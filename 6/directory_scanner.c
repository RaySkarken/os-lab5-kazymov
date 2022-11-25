#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int max_s = 0;
int min_s = 0;
long min_t = 0;
long max_t = 0;

FILE * output_file;

void search_dir(char * dir_name) {
    char dirname[256];
    char element_name[256];
    DIR * dp;
    struct dirent * d;
    struct stat st1;
    dp = opendir(dir_name);
    d = readdir(dp);
    strcpy(dirname,dir_name);
    strcat(dirname,"/");

    while (d != NULL) {
        if (d->d_type == DT_DIR) {
            if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
                strcpy(element_name, dirname);
                strcat(element_name, d->d_name);

                search_dir(element_name);
            }
        } else if (d->d_type == DT_REG) {
            strcpy(element_name, dirname);
            strcat(element_name, d->d_name);
            stat(element_name, &st1);
            if (st1.st_size >= min_s && st1.st_size <= max_s && st1.st_mtime >= min_t && st1.st_mtime <= max_t) {
                fprintf(output_file,"%s  %ld  %ld\n", d->d_name, st1.st_size, st1.st_mtime);
                printf("%s  %ld  %ld\n", d->d_name, st1.st_size, st1.st_mtime);
            }
        }
        d = readdir(dp);
    }
}

int main(int argc, char *argv[]) {
    DIR * dp2;
    struct dirent * d;

    if (argc<7) {
        printf("ERROR! Too few arguments!\n");
        return 1;
    }
    if (argc>7) {
        printf("ERROR! Too many arguments!\n");
        return 1;
    }
    if ((dp2 = opendir(argv[1])) == NULL) {
        printf("ERROR! Current directory is forbidden\n");
        return 1;
    }
    if ((output_file = fopen(argv[2], "w")) == NULL) {
        printf("ERROR! Destination file can't be opened!\n");
        return 1;
    }
    closedir(dp2);

    min_s = atoi(argv[3]);
    max_s = atoi(argv[4]);
    min_t = atol(argv[5]);
    max_t = atol(argv[6]);

    search_dir(argv[1]);
    fclose(output_file);
    return 0;
}
