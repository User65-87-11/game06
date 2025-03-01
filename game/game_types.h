#pragma once

#include "cglm/types.h"

typedef struct{
	//6 planes
	struct {
	 	vec4 a;
		vec4 b;
		vec4 c;
		vec4 d;
	} Plane [6]; 
}Hitbox;

typedef struct{
	size_t len;
	float arr[];
}Float_a;

 