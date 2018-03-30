#ifndef BUFFER_BASE_H
#define BUFFER_BASE_H

#include <stdio.h>

#define BUFFER_SIZE 10

struct MessageStruct{
	int value;
};

typedef struct MessageStruct Message;

struct BufferStruct{
	int size;
	int initial;
	int final;
	int total;
	Message index[BUFFER_SIZE];
} BufferDefault = {
	BUFFER_SIZE,
	0,
	0,
	0
};

typedef struct BufferStruct Buffer;

void bufferPrint(Buffer *pBuffer){
		for (int i = 0; i < pBuffer->size; ++i){
		printf("[%d]",pBuffer->index[i].value);
	}
	printf("\n");
}


void bufferPrintDetails(Buffer *pBuffer){
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

int bufferPush(Buffer *pBuffer, Message element){
	if(bufferIsFull(pBuffer)){
		return -1;
	}
	pBuffer->index[pBuffer->final] = element;
	pBuffer->total++;
	pBuffer->final = (pBuffer->final+1)%pBuffer->size;
	return 1;
}

Message bufferPop(Buffer *pBuffer){
	if(bufferIsEmpty(pBuffer)){
		Message error;
		error.value = -1;
		return error;
	}
	Message element = pBuffer->index[pBuffer->initial];
	pBuffer->index[pBuffer->initial].value = 0;
	pBuffer->total--;
	pBuffer->initial = (pBuffer->initial+1)%pBuffer->size;
	return element;
}


#endif
