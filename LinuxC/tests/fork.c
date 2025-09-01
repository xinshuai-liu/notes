#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main() {

    pid_t pid;
    
    fflush(NULL);

    pid = fork();
    if(pid < 0) {
    }
    if (pid == 0) {
        printf("i'm child...%d, %d\n", getpid(), getppid());
    } else {
        printf("i'm father...%d, %d\n", getpid(), getppid());
    }

    getchar();
    return 0;
}