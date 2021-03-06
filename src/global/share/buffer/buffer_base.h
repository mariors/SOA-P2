#ifndef BUFFER_BASE_H
#define BUFFER_BASE_H

#include <stdio.h>
#include <semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUFFER_SIZE 10

struct MessageStruct{
	int id;
	int key;
	char time[40];
};

typedef struct MessageStruct Message;

struct ActionResponseStruct{
	int idx;
	Message m;
	int time;
};

typedef struct ActionResponseStruct ActionResponse;

typedef struct BufferStruct{
	int size;
	int initial;
	int final;
	int total;
	Message index[BUFFER_SIZE];

} Buffer;

Message createNewMessage(int id, int key);

ActionResponse createNewActionResponse(int idx, Message message);

void printMessage(Message message);

void bufferPrint(Buffer *pBuffer);

void bufferPrintDetails(Buffer *pBuffer);

int bufferIsEmpty(Buffer *pBuffer);

int bufferIsFull(Buffer *pBuffer);

ActionResponse bufferPush(Buffer *pBuffer, Message element);

ActionResponse bufferPop(Buffer *pBuffer);

#endif
