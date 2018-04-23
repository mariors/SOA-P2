#include "buffer_base.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void bufferPrint(Buffer *pBuffer){
	printf("Elementos: ");
	for (int i = 0; i < pBuffer->size; ++i){
		printf("[%d]",pBuffer->index[i].key);
	}
	printf("\n");
}


void bufferPrintDetails(Buffer *pBuffer){
	printf("Buffer\n");
	printf("size: %d\n", pBuffer->size);
	printf("initial: %d\n", pBuffer->initial);
	printf("final: %d\n", pBuffer->final);
	printf("total: %d\n", pBuffer->total);
	bufferPrint(pBuffer);
}

int bufferIsEmpty(Buffer *pBuffer){
	if(pBuffer->total==0){
		return 1;
	}
	return 0;
}

int bufferIsFull(Buffer *pBuffer){
	if(pBuffer->total==pBuffer->size){
		return 1;
	}
	return 0;
}

ActionResponse bufferPush(Buffer *pBuffer, Message element){
	if(bufferIsFull(pBuffer)){
		ActionResponse ar;
		ar.idx = -1;
		return ar;
	}
	pBuffer->index[pBuffer->final] = element;
	ActionResponse ar;
	ar.idx = pBuffer->final;
	pBuffer->total++;
	pBuffer->final = (pBuffer->final+1)%pBuffer->size;
	return ar;
}

ActionResponse bufferPop(Buffer *pBuffer){
	if(bufferIsEmpty(pBuffer)){
		ActionResponse ar;
		ar.idx = -1;
		return ar;
	}
	Message element = pBuffer->index[pBuffer->initial];
	ActionResponse ar = createNewActionResponse(pBuffer->initial, element);
	pBuffer->index[pBuffer->initial].id = 0;
	pBuffer->total--;
	pBuffer->initial = (pBuffer->initial+1)%pBuffer->size;
	return ar;
}


Message createNewMessage(int id, int key){
	Message msg1;
	msg1.id = id;
	msg1.key = key;

	time_t mytime = time(NULL);
	char * time_str = ctime(&mytime);
	time_str[strlen(time_str)-1] = '\0';
	strncpy(msg1.time,time_str,strlen(time_str)-1);
	
	return msg1;
}

ActionResponse createNewActionResponse(int idx, Message message){

	ActionResponse ar;
	ar.idx = idx;
	ar.m = message;

	return ar;

}

void printMessage(Message message){
	printf("Message\n");
	printf("ID: %d\n",message.id);
	printf("Key: %d\n",message.key);
	printf("Current Time: %s\n", message.time);
}
