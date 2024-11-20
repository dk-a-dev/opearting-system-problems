#include "mesg.h"
message msg;

int main(int argc, char const *argv[])
{
    int mq_id;int n;
    if((mq_id = msgget(MKEY1,PERMS | IPC_CREAT))<0)
    {
        printf("Receiver: Error creating message");
        exit(1);
    }
    msgrcv(mq_id,&msg,50,1111L,0);
    write(1,msg.mdata,50);
    msgctl(mq_id,IPC_RMID,NULL);
    return 0;
}
