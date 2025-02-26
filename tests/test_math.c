#include <assert.h>


#define GLMATH_IMPLEMENTATION
#include "glmath.h"
void test_m4_m4_mul();
void test_m4_v4_mul();
void run_math_tests();

void run_math_tests(){
	test_m4_m4_mul();
	test_m4_v4_mul();
}

void test_m4_m4_mul(){
	int m4_size = 16;
	float a_ [m4_size];
	float b_ [m4_size];
	float c_ [m4_size];
	float d_ [m4_size];
	float e_ [m4_size];

	glmath_m4_identity(d_);
	glmath_zero(a_, m4_size);
	glmath_zero(b_, m4_size);
	glmath_zero(c_, m4_size);



	//glmath_m4_print(a_);
	//glmath_m4_print(b_);


	float (*a)[4] = (float (*)[4]) a_;
	float (*b)[4] = (float (*)[4]) b_;

	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;

	b[0][0] = 5;
	b[0][1] = 6;
	b[1][0] = 7;
	b[1][1] = 8;

	glmath_m4_m4_m4_mul_new_to((float*)a,(float*)b, c_);
 
	glmath_m4_identity(d_);
	glmath_m4_m4_m4_mul_new_to(c_,d_, e_);

	
	float (*e)[4] = (float (*)[4]) e_;
 
	assert(e[0][0] == 19.0f);
	assert(e[0][1] == 22.0f);
	assert(e[1][0] == 43.0f);
	assert(e[1][1] == 50.0f);

	 
}

void test_m4_v4_mul(){

	constexpr int  m4_size = 16;
	constexpr int  v4_size = 4;
	float a_ [m4_size];
	float b_ [v4_size];
	glmath_m4_identity(a_);
	float (*a)[4] =(float (*)[4]) a_;
	a[0][0] = 4.0f;
	a[1][1] = 3.0f;
	a[2][2] = 2.0f;
	a[3][3] = 1.0f;

	
	float vec_ []={1.0f,2.0f,3.0f,4.0f};
	
	glmath_m4_v4_v4_mul_new_to(a_, vec_, b_);

	//glmath_v4_print(b_);

	assert(b_[0] == 4.0f);
	assert(b_[1] == 6.0f);
	assert(b_[2] == 6.0f);
	assert(b_[3] == 4.0f);




}	