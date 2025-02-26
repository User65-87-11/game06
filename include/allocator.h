#pragma once

#ifdef ALLOC_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

 

typedef struct {
	void * start;
	size_t cap;
	size_t pos;

}Alloc;
Alloc  alloc_create(size_t size);
void * alloc_new(Alloc a[static 1],size_t size,bool zero);
void * alloc_renew(Alloc a[static 1],void * mem,size_t old_size,size_t new_size );
void alloc_free(Alloc a[static 1]);

#ifdef ALLOC_IMPLEMENTATION


Alloc  alloc_create(size_t size){
	printf("alloc_create:%i\n",size);
	Alloc all={
		.start = malloc(size)
	};
	if(all.start)
	{
		all.cap = size;
		all.pos = 0;
	}
	return all;
}
void * alloc_new(Alloc a[static 1],size_t size,bool zero){
	size_t free_space = a->cap - a->pos;
	if(size > free_space)
	{
		printf("no more mem!\n");
		return nullptr;
	}
	void * ret = a->start + a->pos;
	if(zero)
	{
		for(int i=0; i< size; i++){
			((char*)ret)[i]=0;
		}
	}
	a->pos += size;
	printf("space total:%i free:%i\n",a->cap,a->cap - a->pos);
	return ret;
}
void * alloc_renew(Alloc a[static 1],void * mem,size_t old_size,size_t new_size ){
	size_t free_space = a->cap - a->pos;
	if(new_size > free_space)
	{
		printf("no more mem!\n");
		return nullptr;
	}
	void * prev = mem;
	void * ret = a->start + a->pos;
 
	memcpy(ret, prev,old_size);
	a->pos += new_size;
	printf("space total:%i free:%i\n",a->cap,a->cap - a->pos);
	return ret;
} 
void alloc_free(Alloc a[static 1]){
	if(a->start)
	{
		free(a->start);
	}
	*a = (Alloc){0};
}
#endif