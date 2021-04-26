#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define KEY 123456L

typedef struct msgbuf1 {
    long mtype;      //message type
    char mtext[256]; //uzenet hossza legyen 256 byte
} messageBuffer;

void main() {
    messageBuffer sendBuffer;
    messageBuffer *messagePointer;

    key_t key = KEY;
    int messageID;
    int messageFlag;
    int messageReturn;
    int messageLength;

    //letrehozashoz flagek
    messageFlag = 0666 | IPC_CREAT;
    messageID = msgget(key, messageFlag);
    if (messageID == -1) {
        perror("Nem sikerult letrehozni\n");
        exit(-1);
    }

    messagePointer = &sendBuffer;
    messagePointer->mtype = 1;
    strcpy(messagePointer->mtext, "Uzenetem");
    messageLength = strlen(messagePointer->mtext) + 1;

    messageReturn = msgsnd(messageID, (messageBuffer*)messagePointer, messageLength, messageFlag);
    if (messageReturn == -1) {
        perror("Nem sikerult kuldeni\n");
        exit(-1);
    }

    printf("Kuldve!!\n");

}