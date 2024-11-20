#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Process will sleep for 5 seconds...\n");
    sleep(5);
    printf("Process woke up after sleep.\n");
    return 0;
}

