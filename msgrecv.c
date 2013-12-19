#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define BUFSIZE 512

struct message{
        long msg_type;
        char msg_text[BUFSIZE];

};
int main(int argc, char argv[])
{
        int qid;
        key_t key;
        int len;
        struct message msg;

        if((key = ftok("/",8)) == -1){
                perror("ftok");
                exit(1);
        }
        if((qid = msgget(key, IPC_CREAT|0666)) ==-1)
        {
                perror("msgget");
                exit(1);
        }else{
                printf("the msg id :%d\n",qid);
        }
        memset(msg.msg_text, 0, 512);
        while(1)
        {
                if(msgrcv(qid, &msg, BUFSIZE, 0, 0)<0)
                {
                        perror("msgrecv");
                        exit(1);
                }
                printf("message is :%s\n",(&msg)->msg_text);
                memset(msg.msg_text, 0, 512);
        }

        if((msgctl(qid, IPC_RMID,NULL)) <0)
        {
                perror("msgctl");
                exit(1);
        }
        exit(0);
}
