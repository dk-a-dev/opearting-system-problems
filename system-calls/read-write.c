#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[50];

    if (pipe(fd) == -1) {
        printf("Pipe failed!\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        close(fd[1]);  // Close the writing end in child
        read(fd[0], read_msg, sizeof(read_msg));  // Read message from pipe
        printf("Child Process received: %s\n", read_msg);
        close(fd[0]);
    } else {
        close(fd[0]);  // Close the reading end in parent
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Write message to pipe
        printf("Parent Process sent: %s\n", write_msg);
        close(fd[1]);
    }

    return 0;
}

