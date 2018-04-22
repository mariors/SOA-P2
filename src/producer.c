#include <stdio.h>

//#include "global/procs/message_creation.h"
#include "protected_global.h"
#include "global/procs/message_creation.h"


int main(int argc, char **argv){
	const char * name = "buffdir";
	GlobalState * global;
	double lambda = 1.0;
	printf("*** REGISTERING PRODUCER TO SHARED BUFFER ON %s *** \n", name);
	getGlobalStateProtected(name, &global);
	printGlobalState(global);

	message_creation_loop(global, lambda);

	return 0;
}

