#pragma once

#include <math.h>
#include <stdio.h>


 
typedef float _vec4[4];
typedef float _vec3[4];
typedef _vec4 	_mat4[4];

 

typedef struct{
	union{
		struct{
			float x;
			float y;
			float z;
			float w;
		};
		_vec4 vec;
	};
}vec4;
typedef struct{
	union{
		struct{
			float x;
			float y;
			float z;
		 
		};
		_vec3 vec;
	};
}vec3;


typedef struct{
	union{
		struct{
			vec4 a;
			vec4 b;
			vec4 c;
			vec4 d;
		};
		_mat4 vec;
	};
}mat4;



 

void mmath_zero(float * data,int len);
void mmath_m4_identity(mat4 * m4);
void mmath_m4_print(mat4 * d);
void mmath_v4_print(vec4 * d);
void mmath_m4_v4_v4_mul_new_to(mat4 * m4,vec4 * v4, vec4 * dest);
void mmath_m4_m4_m4_mul_new_to(mat4 * m4A,mat4 * m4B, mat4 * m4out);
void mmath_m4_scale(mat4 * m4, vec4 *v4);
void mmath_m4_translate(mat4 * m4, vec4 *v4);
void mmath_m4_translate_to(mat4 * m4, vec4 *v4,mat4 * m4dst);
void mmath_norm(float * v,int len);
void mmath_m4_rotate_new(mat4 * m4, float r,vec3 *v3);
void mmath_copy(float * src,int src_size,float * dst);

#define mmath_IMPLEMENTATION
#ifdef mmath_IMPLEMENTATION

void mmath_v4_print(vec4 * d){
	printf("Vec4:\n %f %f %f %f\n",d->x,d->y,d->z,d->w);
}

void mmath_m4_print(mat4 * d){


 
	printf("Mat4:\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n",
		d[0 ],d[1 ],d[2 ],d[3 ],
		d[4 ],d[5 ],d[6 ],d[7 ],
		d[8 ],d[9 ],d[10 ],d[11 ],
		d[12 ],d[13 ],d[14 ],d[15 ]
	);
 
}
void mmath_m4_identity(mat4 * m4){
	mmath_zero(m4, 16);
	float (*m)[4] = (float (*)[4])m4;
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
	
	 
}
void mmath_m4_v4_v4_mul_new_to(mat4 * m4,vec4 * v4, vec4 * dest){
	mat4 m = *m4;
	vec4 v = *v4;
 
	 
	dest->x = v.x * m.a.x  + v.y * m.a.y  + v.z * m.a.z  + v.w * m.a.w ;
	dest->y = v.x * m.b.x  + v.y * m.b.y  + v.z * m.b.z  + v.w * m.b.w ;
	dest->z = v.x * m.c.x  + v.y * m.c.y  + v.z * m.c.z  + v.w * m.c.w ;
	dest->w = v.x * m.d.x  + v.y * m.d.y  + v.z * m.d.z  + v.w * m.d.w ;
	

}

void mmath_m4_m4_m4_mul_new_to(mat4 * m4A,mat4 * m4B, mat4 * m4out){
 
	mmath_zero(m4out, 16);
	
 
 

	   // Multiply the matrices
	for (int i = 0; i < 4; i++) {
    	for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
				((float(*)[4])m4out)[i][j] += ((float(*)[4])m4A)[i][k] * ((float(*)[4])m4B)[k][j];
            }
        }
    }
 
}
 
void mmath_m4_scale(mat4 * m4, vec4 *v4){
 
	mmath_m4_identity(m4);
	m4[0][0] = v4[0];
	m4[1][1] = v4[1];
	m4[2][2] = v4[2];
	m4[3][3] = v4[3];
}


void mmath_m4_translate(float * m4, float *v4){
	float (*m)[4] = (float (*)[4])m4;
	mmath_m4_identity(m4);
	m[0][3]	= v4[0];
	m[1][3] = v4[1];
	m[2][3] = v4[2];
	//m[3][3] = v4[3];
}


void mmath_m4_translate_to(float * m4, float *v4,float * m4dst){
	float (*m)[4] = (float (*)[4])m4;
	float (*md)[4] = (float (*)[4])m4dst;
	mmath_m4_identity(m4dst);

	md[0][3] = m[0][3] + v4[0];
	md[1][3] = m[1][3] + v4[1];
	md[2][3] = m[2][3] + v4[2];

	//m[3][3] = v4[3];
}


void mmath_norm(float * v,int len)
{
	float l = 0;
	for(int i=0;i<len;i++)
		l += v[i]*v[i];
	l = sqrt(l);
	for(int i=0;i<len;i++){
		v[i] = v[i] / l;
	}
}


void mmath_m4_rotate_new(float * m4, float r,float *v3){
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




void mmath_zero(float * data,int size){
	for(int i=0;i<size;i++)
	{
		data[i] = 0.f;
	}
}
void mmath_copy(float * src,int src_size,float * dst){
	for(int i=0;i<src_size;i++){
		dst[i] = src[i];
	}
}
 
#endif