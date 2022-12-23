#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


int sync_dirs(char* path1, char* path2, int max_threads) {
  DIR *dir1, *dir2;

  FILE *file1, *file2;

  struct dirent *dt1;
  struct dirent *dt2;

  struct stat stat_f;

  char str[128];

  int existence = 0;
  int thread_cnt = 0;
  int copied_bytes;
  int status;
  
  pid_t ppid;

  if ((dir1=opendir(path1)) == NULL) {
    printf("Error ocurred while opening dir\n");
    return 1;
  }


    dt1 = readdir(dir1);
    while (dt1 != NULL) {
      if (dt1->d_type != DT_DIR) {
      if ((dir2=opendir(path2)) == NULL) {
        printf("Error ocurred while opening dir\n");
        return 1;
      }

      existence = 0;
        dt2 = readdir(dir2);
        while (dt2 != NULL) {
          if (dt2->d_type != DT_DIR) {
            if (strcmp(dt1->d_name, dt2->d_name) == 0) {
              existence=1; // the same file exists
            }
          }

          dt2 = readdir(dir2);
        }

      if (existence == 0) { //File not exist
        char filepath1[strlen(path1) + strlen(dt1->d_name) + 1];
        char filepath2[strlen(path2) + strlen(dt1->d_name) + 1];
          sprintf(filepath1, "%s/%s", path1, dt1->d_name);
        sprintf(filepath2, "%s/%s", path2, dt1->d_name);

        if (thread_cnt == max_threads) {
          while ((ppid = wait(&status)) > 0) {
            printf("\n=============waiting for thread limit %d============\n", thread_cnt);
            thread_cnt = 0;
          }
        }


        pid_t pid = fork();
        thread_cnt++;
          if (pid == 0) {
            if ((file1 = fopen(filepath1, "r")) == NULL || (file2 = fopen(filepath2, "w+")) == NULL) {
              printf("Error open file\n");
            }

          copied_bytes = 0;
          while(!feof (file1)) {
            if (fgets(str, 126, file1)) {
              fputs(str, file2);
              // fprintf(file2, str);
              copied_bytes = copied_bytes + strlen(str);
            }
          }

          printf("file '%s' bytes %d copied by #%d\n", dt1->d_name, copied_bytes - 1, getpid());

          stat(filepath1, &stat_f);
          chmod(filepath2, stat_f.st_mode);


          if (fclose(file1) != 0 || fclose(file2) != 0) {
            printf("Error close file\n");
          }

              return 0;
          }
          }

 

      if (closedir(dir2) != 0) {
        printf("Dir close error\n");
        return 1;
      }
      }
     
      
        dt1 = readdir(dir1);
    }

  if (closedir(dir1) != 0) {
    printf("Dir close error\n");
    return 1;
  }


    while ((ppid = wait(&status)) > 0);
  return 0;
}


int main (int argc, char *argv []) {
  if (argc != 4) {
    printf ("Too few parameters\n");
    return 1;
  }

  char* path1 = argv[1];
  char* path2 = argv[2];
  int max_threads = atoi(argv[3]);

  int result = sync_dirs(path1, path2, max_threads);

  return result;
}