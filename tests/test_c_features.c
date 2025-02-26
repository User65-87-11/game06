#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	
	union {
		float data[];
		struct{
		 
			float x;
			float y;
			float w;
			float h;
		};
		 
	};

}Model1;
constexpr int size =sizeof(int ) * 4;
typedef struct {
	
	int * a;
	int * b;
	int * c;
	int * d;
	
}Refs;

void test_c_refs(){
	void *r = calloc(1, sizeof(Refs));
	((int* )r)[2] = 2;
	 
	Refs *a = (Refs *)r;
	printf("%i %i %i %i\n",a->a,a->b,a->c,a->d);

	free(r);
}

void test_c_size_of_model1();
 
 

void run_c_tests(){
	test_c_size_of_model1();
	void * data = "1234567890abcdefgh";
 
	test_c_refs();
 
}
void test_type(float * f){

	assert(f[0] == 1.0f);
	assert(f[1] == 2.0f);
	assert(f[2] == 3.0f);
	assert(f[3] == 4.0f);
}
void test_c_size_of_model1(){
	Model1 c;
	c.x = 1.0f;
	c.y = 2.0f;
	c.w = 3.0f;
	c.h = 4.0f;
	assert(sizeof(c) == sizeof(float) * 4);

	test_type(c.data);
	 
}
 
 


