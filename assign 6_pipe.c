#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void do_parent(int fd[]);
void do_child(int fd[]);

int main() {
    int fd[2];
    pid_t x;

    pipe(fd);
    x = fork();

    if (x == 0) {
        do_child(fd);
    } else {
        do_parent(fd);
    }

    return 0;
}

void do_parent(int fd[]) {
    close(fd[0]);
    write(fd[1], "Hello World", 12);
    close(fd[1]);
}

void do_child(int fd[]) {
    char buff[12];
    close(fd[1]);
    read(fd[0], buff, 12);
    close(fd[0]);
    printf("Read Msg: %s\n", buff);
}
