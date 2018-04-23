#include "buffer_base.h"

void bufferPrint(Buffer *pBuffer){
	printf("Elementos: ");
	for (int i = 0; i < pBuffer->size; ++i){
		printf("[%d]",pBuffer->index[i].id);
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
		error.id = -1;
		return error;
	}
	Message element = pBuffer->index[pBuffer->initial];
	pBuffer->index[pBuffer->initial].id = 0;
	pBuffer->total--;
	pBuffer->initial = (pBuffer->initial+1)%pBuffer->size;
	return element;
}
