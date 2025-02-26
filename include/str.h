#pragma once

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct{
	char  * data;
	size_t len;

	
}Str; //this is a string ref

typedef struct{
	char  * data;
	size_t len;
	size_t capacity ;
	
}Str_builder; //this is a string ref

/**
void  * data; -> double data[];
Flexible Array Member(FAM) is a feature introduced in the C99 standard of the C programming language.
 */

/**
generics

#define scale(obj,scale)			\
	_Generic(						\
		(obj),						\
		Rectanble_s *: scale_rect,	\
		Circle_s*: scale_circ		\
	)								\
	((obj),(scale))					


*/

 

//  size_t cstr_len(const char c_str[static 1]){
// 	const char *c = c_str;  
//     while (*c != '\0') {   
//         c++;
//     }
// 	return c - c_str ;
// }
// void print_chars(Str * s){
// 	for(int i=0;i<s->len;i++)
// 	{
// 		putchar(s->data[i]);
// 	}
// 	putchar('\n');
// }


Str str_create(const char c_str[static 1]);
void str_builder_append(Str_builder b [static 1], Str s);
void str_free(Str str );
void str_builder_insert(Str_builder b [static 1],Str s,size_t pos);

#define BUIDLER_SIZE 10
#define ARRAYS_IMPLEMENTATION
#ifdef ARRAYS_IMPLEMENTATION

Str_builder str_builder_create(){
 
	Str_builder  b ={0};
	
	b.data = calloc(BUIDLER_SIZE,sizeof(char));
	if(b.data)
	{
		b.capacity = BUIDLER_SIZE;
	}
	return b;
}
void str_builder_append_cstr(Str_builder b [static 1], char c[static 1]){
	printf("str_builder_append_cstr\n");
	Str s = str_create(c);
	str_builder_append(b,s);
	str_free(s);

}
void str_builder_append(Str_builder b [static 1], Str s){
	printf("str_builder_append\n");

	str_builder_insert(b,s,b->len);
}
Str str_builder_to_str(Str_builder b [static 1]){
	printf("str_builder_to_str\n");

	Str s={
		.data = malloc(b->len + 1)
	};
 
 
 
	if(s.data)
	{
		memcpy(s.data, b->data, b->len);
		s.len =  b->len;
		s.data[s.len] = 0;
		
	}
	return  s;
};
static void print_buffer(Str_builder b [static 1]){
	printf("print_buffer\n");
	for(int i=0;i<b->len;i++)
	{
		printf("%02x ",b->data[i]);
	}
	printf("\n");
}
void str_builder_insert(Str_builder b [static 1],Str s,size_t pos){
	printf("str_builder_insert\n");
	
	
	size_t left = b->capacity - b->len  ;
	printf("ins.str:%s\n",s.data);
	printf("b.str:%s\n",b->data);
	print_buffer(b);
	printf("ins: cap:%d, b.len:%d, left:%d, s.len:%d, pos:%d \n",
		b->capacity,
		b->len,
		left,
		s.len,
		pos
	);
	if(s.len >= left)
	{
		size_t ncap = (b->capacity + s.len) * 2 + 1;
		printf("new cap:%d\n",ncap);
		b->data = realloc(b->data,ncap);
		b->capacity = ncap;
	
	}
	if(pos < b->len)
	{

		memcpy(&b->data[b->len],&b->data[pos] , s.len);
		memcpy(&b->data[pos], s.data, s.len);
		
	}else {
		memcpy(&b->data[pos], s.data, s.len);
	}
	b->len+= s.len;
	b->data[b->len] = 0;

};
void str_builder_free(Str_builder b [static 1]){
	if(b && b->data)
	{
		free(b->data);
		
	}
	*b =(Str_builder){0};
}
Str str_create(const char c_str[static 1]){
	size_t cstr_sz = strlen(c_str);

	Str  a = {
		.data = malloc(cstr_sz+1)
	};

	if(a.data)
	{	
		a.len = cstr_sz;
 
		memcpy(a.data,c_str,cstr_sz);
		a.data[a.len] = 0;
	}
	return a;
}
void str_free_array(Str *s [static 1])
{
	 
    while((*s) !=nullptr) {

		Str* ss = *s++;
		free(ss->data);
		 * ss = (Str){0};
		printf("freed \n");
	}
     
     
}
bool str_cmp(Str a ,Str b ){
	if(a.len != b.len) return false;
	
	return strcmp(a.data,b.data) == 0;
}

Str  str_join(Str a ,Str b ){
	size_t s = a.len + b.len;
	Str r ={
		.data =  malloc(s + 1)
	};
	if(r.data)
	{
		r.len = s;

		memcpy(r.data,a.data,a.len);
		memcpy(r.data + a.len,a.data,b.len);
		r.data[r.len] = 0;
	}
 

	return r;
}
void str_free(Str str ){
	if(str.data)
	{
		free(str.data);
	}
	str =(Str){0};
}
#endif


/**

Alignment of char: 1
Alignment of short: 2
Alignment of int: 4
Alignment of long: 8
Alignment of long long: 8
Alignment of float: 4
Alignment of double: 8
Alignment of long double: 16
Alignment of max_align_t: 16
*/