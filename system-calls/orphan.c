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
        sleep(5);  // Ensure parent exits before child
        printf("Orphan Process: PID = %d, Parent PID = %d\n", getpid(), pid);
    } else {
        printf("Parent Process: PID = %d\n", getpid());
        exit(0);  // Parent exits, child becomes orphan
    }

    return 0;
}

