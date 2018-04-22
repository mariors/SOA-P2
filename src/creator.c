#include <stdio.h>

#include "protected_global.h"

int main(int argc, char **argv){
//	const char * name = "MYSHM";
	const char * name = "buffdir";
	GlobalState * global;

	printf("*** CREATING SHARED MEMORY ON ADDRESS %s ***\n",name);
	deleteGlobalStateProtected(name);
	getGlobalStateProtected(name,&global);

	printGlobalState(global);

	return 0;
}
