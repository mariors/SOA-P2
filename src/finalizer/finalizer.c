
#include "../global/protected_global.h"
#include "../global/time/exponential.h"

#define WAIT_SECS 0.7

int main(int argc, char** argv) {
//	if(argc != 2){
//		printf("ERROR: Provide the following arguments(buffer name)\n");
//		return -1;
//	}
	const char * name = argv[1];
//	const char * name = "buffdir";
	GlobalState* global;
	getGlobalStateProtected(name, &global);

	//Set finalizing flag..
	printf("Finalizer: Setting producer flag to DEAD\n");
	setSystemStatus(global, DEAD);
	while(global->producer.total > 0);
	while(global->consumer.total > 0) {
		printf("Finalizer: Sending kill message to buffer\n");
		Message killMessage = createNewMessage(-1,-1);
		wait_arbitrary_secs(WAIT_SECS);
		bufferPushProtected(global, killMessage);
	}
	printf("Finalizer: Done");
	deleteGlobalStateProtected(name);
	


	//TODO: print stats

	return 0;
}