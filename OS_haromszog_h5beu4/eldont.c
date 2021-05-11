#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
// structure for message queue
struct mesg_buffer {
    long mtype;
    char mtext[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
    char next[100];
    int x=0,j=0;
    int oldalak[3];
    
    key = ftok("bemenet.txt", 65);
    
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    msgrcv(msgid, &message, sizeof(message), 1, 0);
  
    printf("A kapott adatok: : %s \n", message.mesg_text);
  
    do
    {
        if(message.mtext[x]!=' ');
        {
            oldalak[j]=(int)message.mtext[x]-48;
            x++;
            j++;
        }
        else
        {
            x++;
        }
    }while(message.mtext[x]!='\0');
    printf("oldalak:\n");
    for(int i=0;i<3;i++)
    {
        printf("%d.oldal: %d",i+1,oldalak[i]);
    }
    strcpy(next,message.mtext);
    msgctl(msgid,IPC_RMID,NULL);
    if(oldalak[0]+oldalak[1]>oldalak[2]&&oldalak[0]+oldalak[2]>oldalak[1]&&oldalak[2]+oldalak[1]>oldalak[0])
    {
        strcat(next," 1");
    }
    else
    {
        strcat(next," 0");
    }
    strcpy(message.mtext,next);
    system("touch kimenet.txt");
    key = ftok("kimenet.txt", 65);
    msgid=msgget(key,0666|IPC_CREAT);
    message.mtype=1;
    msgsnd(msqid,&message,sizeof(message),0);
    printf("A kimeneti fileba küldött, kiegészített adatok: %s \n",message.mtext);
    return 0;
}