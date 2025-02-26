#pragma once

 
#include "cglm/types.h"
 

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
		ivec4 vec;
		struct{
			int x;
			int y;
			int z;
			int w;
		};
	};
} Vec4is;


typedef struct{
	union{
		vec3 vec;
		struct{
			float x;
			float y;
			float z;
		};
	};
} Vec3s;

typedef struct{
	union{
		ivec3 vec;
		struct{
			int x;
			int y;
			int z;
		};
	};
} Vec3is;

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