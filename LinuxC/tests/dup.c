#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    int fd = open("filesize.c",O_RDWR);
    if (fd < 0) return -1;

    int new_fd = dup2(fd, 2);

    printf("%d,%d\n", fd, new_fd);


}