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
	printf("before mutex\n");
	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	printf("inside mutex");
	int res = bufferPush(&global->buffer,element);
	sem_post(&global->buffer.mutex);
	printf("after mutex");
	int seconds = end - start;
	return res;
}

int bufferIsEmptyProtected(GlobalState *global){
	return bufferIsEmpty(&global->buffer);
}

int bufferIsFullProtected(GlobalState *global){
	return bufferIsFull(&global->buffer);
}

Message bufferPopProtected(GlobalState *global){
	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	Message res = bufferPop(&global->buffer);
	sem_post(&global->buffer.mutex);
	int seconds = end - start;
	return res;
}
