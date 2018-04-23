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

ActionResponse bufferPushProtected(GlobalState *global,Message element){

	printf("before mutex\n");
	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	printf("inside mutex");
	ActionResponse ar = bufferPush(&global->buffer,element);
	sem_post(&global->buffer.mutex);
	printf("after mutex");
	int seconds = end - start;
	ar.time = seconds;
	return ar;
}

int bufferIsEmptyProtected(GlobalState *global){
	return bufferIsEmpty(&global->buffer);
}

int bufferIsFullProtected(GlobalState *global){
	return bufferIsFull(&global->buffer);
}

ActionResponse bufferPopProtected(GlobalState *global){

	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	ActionResponse ar = bufferPop(&global->buffer);
	sem_post(&global->buffer.mutex);
	int seconds = end - start;
	ar.time = seconds;
	return ar;
}

int setSystemStatus(GlobalState* global,status_code s){
	//todo; semaphore
	global->status = s;
}

int checkSystemAlive(GlobalState* global){
	//todo; semaphore
	return global->status == RUNNING;
}
