#include "protected_global.h"


int getGlobalStateProtected(const char *name, GlobalState **global){
	return getGlobalState(name,global);
}

void deleteGlobalStateProtected(const char *name){
	deleteGlobalState(name);
}

int registerProducerProtected(GlobalState *global){
	return registerProducer(global);
}

void unregisterProducerProtected(GlobalState *global){
	unregisterProducer(global);
}

int registerConsumerProtected(GlobalState *global){
	return registerConsumer(global);
}

void unregisterConsumerProtected(GlobalState *global){
	unregisterConsumer(global);
}

int bufferPushProtected(GlobalState *global,Message element){
//	printf("before mutex\n");
//	sem_wait(&global->buffer.mutex);
//	printf("inside mutex");
	int res = bufferPush(&global->buffer,element);
//	sem_post(&global->buffer.mutex);
//	printf("after mutex");
	return res;
}

int bufferIsEmptyProtected(GlobalState *global){
	return bufferIsEmpty(&global->buffer);
}

int bufferIsFullProtected(GlobalState *global){
	return bufferIsFull(&global->buffer);
}

Message bufferPopProtected(GlobalState *global){
//	sem_wait(&global->buffer.mutex);
	Message res = bufferPop(&global->buffer);
//	sem_post(&global->buffer.mutex);
	return res;
}

int setSystemStatus(GlobalState* global,status_code s){
	//todo; semaphore
	global->status = s;
}

int checkSystemAlive(GlobalState* global){
	//todo; semaphore
	return global->status == RUNNING;
}