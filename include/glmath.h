#pragma once

#include <math.h>
#include <stdio.h>

void glmath_zero(float * data,int len);
void glmath_m4_identity(float * m4);
void glmath_m4_print(float * d);
void glmath_v4_print(float * d);
void glmath_m4_v4_v4_mul_new_to(float * m4,float * v4, float * dest);
void glmath_m4_m4_m4_mul_new_to(float * m4A,float * m4B, float * m4out);
void glmath_m4_scale(float * m4, float *v4);
void glmath_m4_translate(float * m4, float *v4);
void glmath_m4_translate_to(float * m4, float *v4,float * m4dst);
void glmath_norm(float * v,int len);
void glmath_m4_rotate_new(float * m4, float r,float *v3);
void glmath_copy(float * src,int src_size,float * dst);


#ifdef GLMATH_IMPLEMENTATION

void glmath_v4_print(float * d){
	printf("Vec4:\n %f %f %f %f\n",d[0 ],d[1 ],d[2 ],d[3 ]);
}

void glmath_m4_print(float * d){


 
	printf("Mat4:\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n",
		d[0 ],d[1 ],d[2 ],d[3 ],
		d[4 ],d[5 ],d[6 ],d[7 ],
		d[8 ],d[9 ],d[10 ],d[11 ],
		d[12 ],d[13 ],d[14 ],d[15 ]
	);
 
}
void glmath_m4_identity(float * m4){
	glmath_zero(m4, 16);
	float (*m)[4] = (float (*)[4])m4;
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
	 
}
void glmath_m4_v4_v4_mul_new_to(float * m4,float * v4, float * dest){
	float (*m)[4] = (float (*)[4])m4;
	dest[0] = v4[0] * m[0][0] + v4[1] * m[0][1] + v4[2] * m[0][2] + v4[3] * m[0][3];
	dest[1] = v4[0] * m[1][0] + v4[1] * m[1][1] + v4[2] * m[1][2] + v4[3] * m[1][3];
	dest[2] = v4[0] * m[2][0] + v4[1] * m[2][1] + v4[2] * m[2][2] + v4[3] * m[2][3];
	dest[3] = v4[0] * m[3][0] + v4[1] * m[3][1] + v4[2] * m[3][2] + v4[3] * m[3][3];
	
}

void glmath_m4_m4_m4_mul_new_to(float * m4A,float * m4B, float * m4out){
	float (*a)[4] = (float (*)[4])m4A;
	float (*b)[4] = (float (*)[4])m4B;
	float (*o)[4] = (float (*)[4])m4out;
	glmath_zero(m4out, 16);
 

	   // Multiply the matrices
	for (int i = 0; i < 4; i++) {
    	for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                o[i][j] += a[i][k] * b[k][j];
            }
        }
    }

}
 
void glmath_m4_scale(float * m4, float *v4){
	float (*m)[4] = (float (*)[4])m4;
	glmath_m4_identity(m4);
	m[0][0] = v4[0];
	m[1][1] = v4[1];
	m[2][2] = v4[2];
	m[3][3] = v4[3];
}


void glmath_m4_translate(float * m4, float *v4){
	float (*m)[4] = (float (*)[4])m4;
	glmath_m4_identity(m4);
	m[0][3]	= v4[0];
	m[1][3] = v4[1];
	m[2][3] = v4[2];
	//m[3][3] = v4[3];
}


void glmath_m4_translate_to(float * m4, float *v4,float * m4dst){
	float (*m)[4] = (float (*)[4])m4;
	float (*md)[4] = (float (*)[4])m4dst;
	glmath_m4_identity(m4dst);

	md[0][3] = m[0][3] + v4[0];
	md[1][3] = m[1][3] + v4[1];
	md[2][3] = m[2][3] + v4[2];

	//m[3][3] = v4[3];
}


void glmath_norm(float * v,int len)
{
	float l = 0;
	for(int i=0;i<len;i++)
		l += v[i]*v[i];
	l = sqrt(l);
	for(int i=0;i<len;i++){
		v[i] = v[i] / l;
	}
}


void glmath_m4_rotate_new(float * m4, float r,float *v3){
	float x = v3[0];
	float y = v3[1];
	float z = v3[2];
	float (*m)[4] = (float (*)[4])m4;
	
	 
	m[0][0] = cos(r) + x*x*(1 - cos(r));
	m[1][0] = y*x*(1 - cos(r)) + z*sin(r);
	m[2][0] = z*x*(1 - cos(r)) - y*sin(r);
	m[3][0] = 0;

	m[0][1] = x*y*(1 - cos(r)) - z*sin(r);
	m[1][1] = cos(r) + y*y*(1 - cos(r));
	m[2][1] = z*y*(1 - cos(r)) + x*sin(r);
	m[3][1] = 0;

	m[0][2] = x*z*(1 - cos(r)) + y*sin(r);
	m[1][2] = y*z*(1 - cos(r)) - x*sin(r);
	m[2][2] = cos(r) + z*z*(1 - cos(r));
	m[3][2] = 0;

	m[0][3] = 0;
	m[1][3] = 0 ;
	m[2][3] = 0 ;
	m[3][3] = 1;

	//m[3][3] = v4[3];
}




void glmath_zero(float * data,int size){
	for(int i=0;i<size;i++)
	{
		data[i] = 0.f;
	}
}
void glmath_copy(float * src,int src_size,float * dst){
	for(int i=0;i<src_size;i++){
		dst[i] = src[i];
	}
}
 
#endif