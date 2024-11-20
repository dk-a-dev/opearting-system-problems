#include "mesg.h"
message msg;

int main(int argc, char const *argv[])
{
    int mq_id;int n;
    if((mq_id = msgget(MKEY1,PERMS | IPC_CREAT))<0)
    {
        printf("Sender: Error creating message");
        exit(1);
    }
    msg.mtype = 1111L;
    n=read(0,msg.mdata,50);
    msg.mdata[n]='\0';
    msgsnd(mq_id,&msg,50,0);
    return 0;
}
