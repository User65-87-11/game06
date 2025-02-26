#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <../external/cglm/cglm.h>
#include <../external/cglm/types.h>
#include <../external/cglm/mat4.h>

 
 

 
#include <stdalign.h>

 
 

typedef __attribute__((aligned(16))) float v4[4];
typedef __attribute__((aligned(16))) v4 m4[4];
typedef __attribute__((aligned(16))) float fa;

void test_align(){
 
	v4 v;
	m4 m;
	float * vv[4];//just means 4 ptrs
	
	fa f = 5;
	
 
	 

	printf("alignment: %i\n",alignof(v4));
	printf("size mat4: %i\n",sizeof(mat4));
	printf("size float * [4]: %i\n",sizeof(float * [4]));

	printf("size m4: %i\n",sizeof(m4));
	printf("size v4: %i\n",sizeof(v4));
	printf("size vp[4]: %i\n",sizeof(vv));

	float a[4];

	printf("size a %i, float: %i\n",sizeof(a),sizeof(float));
	 
	alignas(16) float  b[4][4];
	printf("size b  %i, float[4][4]: %i, alignof(%i)\n",
		sizeof(b),
		sizeof(float * [4]),
		alignof(b)
	);
 
	printf("\n");
	
}

 
 


void run_test_align(){
	test_align();
}