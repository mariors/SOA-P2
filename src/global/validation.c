//
// Created by aleph on 4/23/18.
//

#include <stdio.h>

#include "validation.h"


int validate_lambda(double lambda) {
	int res = lambda > 0.0 && 1 / lambda < 1000;
	if(!res) {
		fprintf(stderr,"ERROR: lambda parameter must be greater than 0, and 1/lambda < 1000\n");
	}
	return res;
}