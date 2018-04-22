#include "global/global.h"

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
	return bufferPush(&global->buffer,element);
}

int bufferIsEmptyProtected(GlobalState *global){
	return bufferIsEmpty(&global->buffer);
}

int bufferIsFullProtected(GlobalState *global){
	return bufferIsFull(&global->buffer);
}

Message bufferPopProtected(GlobalState *global){
	return bufferPop(&global->buffer);
}