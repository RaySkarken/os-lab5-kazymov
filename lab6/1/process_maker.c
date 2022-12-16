#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


const int STRING_SIZE = 200;

void check_current_time(char* time_string)
{
    time_t timer;
    timer = time(NULL);
    struct tm* current_time = localtime(&timer);
    char* time_str[40] = {0};
    strftime(*time_str, 40, "%H:%M:%S", current_time);

    struct timespec now_timespec;
    clock_gettime(CLOCK_MONOTONIC, &now_timespec);
    long milliseconds = now_timespec.tv_nsec / 1000000;

    snprintf(time_string, STRING_SIZE, "Текущее время: %s.%ld", time_str, milliseconds);
}

void print_pid_info(pid_t pid)
{
    char time_string[STRING_SIZE];
    if (pid == 0)
    {
        check_current_time(time_string);
        printf("Это Дочерний процесс, его pid=%d. %s\n", getpid(), time_string);
        check_current_time(time_string);
        printf("    pid его Родительского процесса=%d %s\n", getppid(), time_string);
    }
    else if (pid > 0)
    {
        check_current_time(time_string);
        printf("Это Родительский процесс pid=%d %s\n", getpid(), time_string);
    }
    else
    {
        printf("Ошибка вызова fork, потомок не создан\n");
    }
}

int main()
{
    pid_t pid1 = fork();
    print_pid_info(pid1);

    if (pid1 > 0)
    {
        pid_t pid2 = fork();
        print_pid_info(pid2);
        if (pid2 > 0)
        {
            system("ps -x");
        }
    }

    return 0;
}
