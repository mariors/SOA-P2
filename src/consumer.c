#include <stdio.h>

#include "protected_global.h"
#include "global/procs/message_consumption.h"

int main(int argc, char **argv){
	const char * name = "buffdir";
	GlobalState * global;

	double lambda = 1.0;
	printf("*** REGISTERING CONSUMER TO SHARED BUFFER ON %s *** \n", name);
	getGlobalStateProtected(name,&global);
	printf("\n\nInitial buffer state\n");
	printGlobalState(global);
	printf("\n\n");

	message_consumption_on_loop(global,lambda);

	printGlobalState(global);

	return 0;
}

