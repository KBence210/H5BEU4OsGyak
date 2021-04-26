#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define KEY 123456L

typedef struct msgbuf1 {
    long mtype;      //message type
    char mtext[256]; //uzenet hossza legyen 256 byte
} messageBuffer;

void main() {
    messageBuffer recieveBuffer;
    messageBuffer *messagePointer = &recieveBuffer;

    struct msqid_ds descriptor;
    struct msqid_ds *buffer = &descriptor;

    key_t key = KEY;
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

}