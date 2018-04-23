
#include "../global/protected_global.h"
#include "../global/time/exponential.h"

#define WAIT_SECS 0.7


int main(int argc, char** argv) {
	if(argc != 2){
		printf("ERROR: Provide the following arguments(buffer name)\n");
		return -1;
	}
	const char * name = argv[1];
	GlobalState* global;
	getGlobalStateProtected(name, &global);

	//Collecting before deletion stats
	int producers = global->producer.total;
	int consumers = global->consumer.total;


	printf("Starting system finalization. Current global state: \n");
	printGlobalState(global);

	//Set finalizing flag..
	printf("Finalizer: Setting producer flag to DEAD\n");
	setSystemStatus(global, DEAD);

	while(global->consumer.total > 0) {
		printf("Finalizer: Sending kill message to buffer\n");
		Message killMessage = createNewMessage(-1,-1);
		wait_arbitrary_secs(WAIT_SECS);
		bufferPushProtected(global, killMessage);
	}
	printf("\n\n*****************\n");
	printf("Finalizer: Done");

	printf("Number of active producers at finalization time: %d\n", producers);
	printf("Number of active consumers at finalization time: %d\n", consumers);

	printf("Global state in the end: \n");
	printGlobalState(global);
	printf("*****************\n");

	return 0;
}