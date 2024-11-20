#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MKEY1 5543L
#define MKEY2 4354L
#define PERMS 0666

typedef struct 
{
    long mtype;
    char mdata[50];
}message;x
