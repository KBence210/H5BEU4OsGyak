#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define KEY 777777L

typedef struct msgbuf1 {
    long mtype;
    char mtext[128];
} messageBuffer;

void main() {
    pid_t childPid;
    key_t key = KEY;

    childPid = fork();
    if (childPid == 0) {
        messageBuffer recieveBuffer;
        messageBuffer *messagePointer = &recieveBuffer;

        struct msqid_ds descriptor;
        struct msqid_ds *buffer = &descriptor;
        int messageID;
        int messageFlag = 0;
        int messageReturn;
        int messageLength = 20;
        int messageType = 0;
        
        messageID = msgget(key, 0);

        messageReturn = msgctl(messageID, IPC_STAT, buffer);
        printf("Az uzenetek szama: %ld\n",buffer->msg_qnum);

        
        while (buffer->msg_qnum) {
            messageReturn = msgrcv(messageID, (messageBuffer*)messagePointer, messageLength, messageType, messageFlag);
            printf("Kapott uzenet: %s\n", messagePointer->mtext);
            messageReturn = msgctl(messageID, IPC_STAT, buffer);
        }

    } else {
        messageBuffer sendBuffer;
        messageBuffer *messagePointer;

        int messageID;
        int messageFlag;
        int messageReturn;
        int messageLength;

        messageFlag = 0666 | IPC_CREAT;
        messageID = msgget(key, messageFlag);
        if (messageID == -1) {
            perror("Nem sikerult letrehozni\n");
            exit(-1);
        }

        messagePointer = &sendBuffer;
        messagePointer->mtype = 1;
        char *messages[] = {"elso", "masodik", "harmadik"};
        
        for (int i = 0; i < 3; i++) {
            strcpy(messagePointer->mtext, messages[i]);
            messageLength = strlen(messagePointer->mtext) + 1;

            messageReturn = msgsnd(messageID, (messageBuffer*)messagePointer, messageLength, messageFlag);
            if (messageReturn == -1) {
                perror("Nem sikerult kuldeni\n");
                exit(-1);
            }
        }
        
        printf("Kuldve!!\n");        
    }
    
}