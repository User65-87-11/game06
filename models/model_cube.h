#pragma once
 



#include "cglm/affine.h"
#include "cglm/vec3.h"
 
#include <cglm/mat4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>
#include <stdint.h>

 
constexpr static size_t max_sides = 6;


typedef struct Model_cube Model_cube;

typedef struct Model_cube_inst
{
	int arr_idx;
	int tilex,tiley;
	int ID;


	
 
}Model_cube_inst;
 

typedef struct Model_cube{
 
 
	unsigned int VAO;
	unsigned int VBO_NORM,VBO_COL,VBO_VERT,VBO_TEXTCOORD,VBO_TRANSFORM;
	unsigned int VAO_ID, VBO_ID;
	unsigned int texture01;
	size_t inst_cnt;
	Model_cube_inst  *insts ;

	
	//wrong use , but ok
	mat4 * m4_models ;
	vec4 * v4_colors ;

	
	
  
} Model_cube;

 
extern void model_cube_free(Model_cube  *p [static 1]);
//extern void model_cube_draw(Model_cube p [static 1]);
extern void model_cube_move_to_tile(Model_cube_inst p[static 1],int x,int y);
extern void model_cube_update_buffers(Model_cube p [static 1]);
extern void model_cube_init(Model_cube * ref[static 1]);
 

#ifdef MODEL_CUBE_IMPLEMENTATION


#include <math.h>
#include <cglm/cglm.h>
#include <cglm/types.h>

#include <glad/gl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "camera.h"
#include "cglm/vec4.h"
 


#include "model_floor.h"

#include "model_2d.h"
#include "cglm/affine-pre.h"
#include "cglm/mat4.h"
#include "../game/buffer.h"

#include "glm_wrap.h"
#include "../game/wavefront.h"

#include "../game/load_texture.h"
 
extern Camera_s *camera;
extern Model_floor * model_floor;
extern Model_cube * model_cube;


void model_id_itof4(int id,float *v4)
{
 

    // Convert the ARGB components to floats in the range [0.0, 1.0]
    v4[3] =  1.0f;
    v4[2] =  ((id >> 16) & 0xFF) / 255.0f;
    v4[1] =  ((id >> 8) & 0xFF) / 255.0f;
    v4[0] =  ((id ) & 0xFF) / 255.0f;

	 
}
void model_cube_init(Model_cube * ref[static 1]){
 
	if(*ref)
	{
		model_cube_free(ref);
	}
	*ref = calloc(1,sizeof(Model_cube));
	
 
	
	 
	model_cube->inst_cnt = 2;

 
	model_cube->insts = calloc(model_cube->inst_cnt,sizeof(Model_cube_inst) );
	model_cube->m4_models = malloc(model_cube->inst_cnt*sizeof(mat4));
	model_cube->v4_colors = malloc(model_cube->inst_cnt*sizeof(vec4));
	vec4 * v4_inst_ids = malloc(model_cube->inst_cnt*sizeof(vec4));
	 

 
	float cellSize = camera->tile_size;
	float scale = cellSize ;
	for(int i=0;i<model_cube->inst_cnt;i++)
 
	{
	 	int tiley = i / cellSize ;
		int tilex = i % (int)cellSize;
		printf("pos: %i , %i \n",tilex,tiley);
 
		glm_mat4_identity((vec4 *)&model_cube->m4_models[i]);
 
		vec4 z = {scale,scale,scale,1.f};
		glm_scale((vec4 *)&model_cube->m4_models[i], z);


		float * color  ;
	
		float black [4]={0.0f,0.0f,0.0f,1.0f};
		float white [4]={1.0f,1.0f,1.0f,1.0f};

		color = white;
		

		model_cube_move_to_tile(&model_cube->insts[i], tilex, tiley);
	
		

 

		glm_vec4_copy(color, (float *)&model_cube->v4_colors[i]);
		
		int  temp_id =  0xff000000 +i;
		model_cube->insts[i].arr_idx  = i;
		model_cube->insts[i].ID = temp_id;

		float  *f = (float*)&(v4_inst_ids[i]);
		
		model_id_itof4(temp_id,f);
 
	}

	
	
	constexpr int vsize = max_sides*6*3;
	constexpr int vert_cnt = max_sides*6;
	constexpr int triang_cnt = max_sides*2;
 
 
 
	load_texture(&model_cube->texture01,"../assets/32x32_texture01.png");
 
 
 
	glGenVertexArrays(1,&model_cube->VAO);
	glGenBuffers(1, &model_cube->VBO_VERT);
	glGenBuffers(1, &model_cube->VBO_COL);
	glGenBuffers(1, &model_cube->VBO_NORM);
	glGenBuffers(1, &model_cube->VBO_TRANSFORM);
	glGenBuffers(1, &model_cube->VBO_TEXTCOORD);
 
 
	 
	//--
	glBindVertexArray( model_cube->VAO);
	 

	WF *wf;
	wf_load(&wf, "../assets/models/cube01.obj");

	float * vdata;
	size_t vdata_len ;
 	wf_get_vert_data(wf, &vdata, &vdata_len);
 
	buffer_describe_vec3(model_cube->VBO_VERT,GL_ARRAY_BUFFER, 0, 0);
	buffer_set_data(model_cube->VBO_VERT,GL_ARRAY_BUFFER, vdata_len,vdata, GL_STATIC_DRAW);
	
 

	//--colors

	buffer_describe_vec4(model_cube->VBO_COL,GL_ARRAY_BUFFER, 1, 1);
	buffer_set_data(model_cube->VBO_COL,GL_ARRAY_BUFFER,model_cube->inst_cnt*sizeof(float[4]), model_cube->v4_colors, GL_DYNAMIC_DRAW);
 
	
 
 

	float * tdata;
	size_t tdata_len ;
 	wf_get_textcoord_data(wf, &tdata, &tdata_len);


	buffer_describe_vec2(model_cube->VBO_TEXTCOORD, GL_ARRAY_BUFFER, 0, 2);
	buffer_set_data(model_cube->VBO_TEXTCOORD, GL_ARRAY_BUFFER, tdata_len, tdata, GL_STATIC_DRAW);
	
	

	float * ndata;
	size_t ndata_len ;
 	wf_get_textcoord_data(wf, &ndata, &ndata_len);


	//normals 2*vec3 per triang
	//norm per vertex
	buffer_describe_vec3(model_cube->VBO_NORM,GL_ARRAY_BUFFER, 0, 3);
	buffer_set_data(model_cube->VBO_NORM,GL_ARRAY_BUFFER, ndata_len, ndata, GL_STATIC_DRAW);
	
 
///--- model matrix

	buffer_describe_mat4(model_cube->VBO_TRANSFORM, GL_ARRAY_BUFFER,1, 10);
	buffer_set_data(model_cube->VBO_TRANSFORM, GL_ARRAY_BUFFER, model_cube->inst_cnt*sizeof(float[16]), model_cube->m4_models, GL_DYNAMIC_DRAW);

	//unset data
 
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 


	//--
	glGenVertexArrays(1,&model_cube->VAO_ID);
	glGenBuffers(1,&model_cube->VBO_ID);
 
 
	glBindVertexArray(model_cube->VAO_ID); 

	buffer_describe_vec4(model_cube->VBO_ID,GL_ARRAY_BUFFER, 1, 1);
	buffer_set_data(model_cube->VBO_ID,
		GL_ARRAY_BUFFER,
		model_cube->inst_cnt*sizeof(vec4),  
		v4_inst_ids, 
		GL_STATIC_DRAW);

	buffer_describe_vec3(model_cube->VBO_VERT,GL_ARRAY_BUFFER, 0, 0);
	buffer_describe_mat4(model_cube->VBO_TRANSFORM,GL_ARRAY_BUFFER, 1, 10);
 
	 
	glBindVertexArray(0); 

	free(vdata);
	free(tdata);
	free(ndata);
	free(v4_inst_ids);
}
 

void model_cube_move_to_tile(Model_cube_inst p[static 1],int x,int y){

 
	p->tilex = x;
	p->tiley = y;

	float cellSize = camera->tile_size;
	float scale = cellSize ;


	float posx = x  * scale ;
	float posy = y  * scale;
	vec4 v ={posx,posy,0.0f ,1.0f};
 
	
	// glm_mat4_identity((vec4 *)&model_cube->m4_models[p->arr_idx]);

	// vec4 z = {scale,scale,scale,1.f};
	// glm_scale((vec4 *)&model_cube->m4_models[p->arr_idx], z);

	glm_translate((vec4 *)&model_cube->m4_models[p->arr_idx],v);
	
 
	 
	 
	
}

// void model_cube_draw(Model_cube p [static 1]){
 
// 	glBindTexture(GL_TEXTURE_2D, p->texture01);
// 	glBindVertexArray(p->VAO);
// 	glDrawArraysInstanced(GL_TRIANGLES,0,max_sides*6,p->inst_cnt);

	
// }
void model_cube_free(Model_cube  *p [static 1]){
	if((*p)){
		free((*p)->insts);
		free((*p)->m4_models);
		free((*p)->v4_colors);
		free((*p));
	}
	(*p) = nullptr;
	
}
 
 
#endif

/**
	1.window normal mouse pos
	2.dot product for all objects

*/