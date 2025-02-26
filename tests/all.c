
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "test_math.c"
#include "test_c_features.c"
#include "test_align.c"
#include "test2.c"
void main_run_tests();


int main() {
	 
	main_run_tests();
    return 0;
}

 
void main_run_tests(){
	// run_math_tests();
	// run_c_tests();
	run2_tests();
	//run_test_align();
}
 