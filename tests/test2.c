#pragma once

#define CGLM_ALL_UNALIGNED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
 
 

#include <../external/cglm/cglm.h>
#include <../external/cglm/types.h>
#include <../external/cglm/mat4.h>

 
 

 
#include <stdalign.h>

typedef struct{
	union{
		vec4 vec;
		struct{
			float x;
			float y;
			float z;
			float w;
		};
	};
} Vec4s;
typedef struct{
	union{
		mat4 mat;
		struct{
			Vec4s a;
			Vec4s b;
			Vec4s c;
			Vec4s d;
		};
	};
	 
} Mat4s;

void test2_type(){
  
	//float   m[4][4];

	mat4 mat;
	Mat4s m;

	printf("ading of:   %i\n", alignof(m));
	printf("ading of:   %i\n", alignof(mat));
	

 	glm_mat4_identity(m.mat);
	 
 
	
}

 
 


void run2_tests(){
	test2_type();
}