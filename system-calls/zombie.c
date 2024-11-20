#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process (Zombie): PID = %d\n", getpid());
        exit(0);  // Child process exits, creating a zombie
    } else {
        printf("Parent Process: PID = %d\n", getpid());
        sleep(3);  // Parent sleeps, child becomes a zombie
        system("ls -a");  // Display zombie process
    }

    return 0;
}

