#pragma once


#ifdef STR_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#endif

#include "allocator.h"

typedef struct{
	char  * data;
	size_t len;

	
}Str; //this is a string ref

typedef struct{
	char  * data;
	size_t len;
	size_t capacity ;
	Alloc *al;
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
#define BUIDLER_SIZE 10

Str str_create(const char c_str[static 1] , Alloc * al);
Str str_copy(Str src,Alloc * mem);
Str  str_join(Str a ,Str b ,Alloc * all);
bool str_cmp(Str a ,Str b );



void str_builder_free(Str_builder b [static 1]);
void str_builder_append(Str_builder b [static 1], Str s );
void str_builder_insert(Str_builder b [static 1],Str s,size_t pos ) ;
Str_builder str_builder_create( Alloc * al);
void str_builder_append_cstr(Str_builder b [static 1], char c[static 1]);
Str str_builder_to_str(Str_builder b [static 1]);
static void print_buffer(Str_builder b [static 1]);


#ifdef STR_IMPLEMENTATION

Str_builder str_builder_create( Alloc * al){
 
	Str_builder  b ={0};
	
	//b.data = calloc(BUIDLER_SIZE,sizeof(char));
	b.data = alloc_new(al, BUIDLER_SIZE * sizeof(char) + 1, true);
	b.al = al;
	if(b.data)
	{
		b.capacity = BUIDLER_SIZE;
	}
	return b;
}
void str_builder_append_cstr(Str_builder b [static 1], char c[static 1]){
	printf("str_builder_append_cstr\n");
	Str s = str_create(c,b->al);
	str_builder_append(b,s);
	//str_free(&s);

}
void str_builder_append(Str_builder b [static 1], Str s){
	printf("str_builder_append\n");

	str_builder_insert(b,s,b->len);
}
Str str_builder_to_str(Str_builder b [static 1]){
	printf("str_builder_to_str\n");

	Str s={
		.data = alloc_new(b->al,b->len + 1,false)
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
	
	
	size_t left = b->capacity - b->len -1 ;
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
		size_t new_cap = b->capacity * 2 +1;
		if( b->capacity / s.len == 0)
		{
			new_cap = s.len * 2 +1;
		}
	 
		printf("new cap:%d\n",new_cap);
		b->data = alloc_renew(b->al,b->data,b->len,new_cap );
		b->capacity = new_cap;
	
	}
	if(pos < b->len)
	{

		memcpy(&b->data[b->len],&b->data[pos] , s.len);
		memcpy(&b->data[pos], s.data, s.len);
		
	}else {
		memcpy(&b->data[pos], s.data, s.len);
	}
	b->len+= s.len;
	b->data[b->len] = '\0';

};
 
Str str_copy(Str src,Alloc * mem){
	Str ret = {
		
		.data = alloc_new(mem, src.len+1, false)
	};
	memcpy(ret.data, src.data, src.len);
	ret.data[src.len] ='\0';

	return ret;
};
Str str_create(const char c_str[static 1],Alloc * all){
	size_t cstr_sz = strlen(c_str);

	Str  a = {
		.data = alloc_new(all,cstr_sz+1,false)
	};

	if(a.data)
	{	
		a.len = cstr_sz;
 
		memcpy(a.data,c_str,cstr_sz);
		a.data[a.len] = '\0';
	}
	return a;
}
 
bool str_cmp(Str a ,Str b ){
	if(a.len != b.len) return false;
	
	return strcmp(a.data,b.data) == 0;
}

Str  str_join(Str a ,Str b ,Alloc * all){
	size_t s = a.len + b.len;
	Str r ={
		.data =  alloc_new(all, s+1, false)
	};
	if(r.data)
	{
		r.len = s;

		memcpy(r.data,a.data,a.len);
		memcpy(r.data + a.len,a.data,b.len);
		r.data[r.len] = '\0';
	}
 

	return r;
}
 
#endif

