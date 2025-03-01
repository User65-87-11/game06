#pragma once
 



#include "cglm/affine.h"
#include "cglm/vec3.h"
 
#include <cglm/mat4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>

 
constexpr static size_t max_sides = 6;

typedef struct Model_cube Model_cube;

typedef struct Model_cube_inst
{
	int idx;
	int tilex,tiley;
	


	
 
}Model_cube_inst;
 

typedef struct Model_cube{
 
	unsigned int shader_id;
	unsigned int VAO;
	unsigned int VBO_NORM,VBO_COL,VBO_VERT,VBO_TEXTCOORD,VBO_TRANSFORM;
	unsigned int texture01;
	size_t inst_cnt;
	Model_cube_inst  *insts ;

	 
	mat4 * m4_models ;
	vec4 * v4_colors ;
	struct {

	}s;
	
  
} Model_cube;

 
extern void model_cube_free(Model_cube  *p [static 1]);
extern void model_cube_draw(Model_cube p [static 1]);
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


 
void model_cube_init(Model_cube * ref[static 1]){
 
	if(*ref)
	{
		model_cube_free(ref);
	}
	*ref = calloc(1,sizeof(Model_cube));
	
 
	
	 
	model_cube->inst_cnt = 1;

	if(model_cube->inst_cnt > model_floor->num_inst) 
	{
		model_cube->inst_cnt = model_floor->num_inst;
	}
	model_cube->insts = calloc(model_cube->inst_cnt,sizeof(Model_cube_inst) );
	model_cube->m4_models = malloc(model_cube->inst_cnt*sizeof(mat4));
	model_cube->v4_colors = malloc(model_cube->inst_cnt*sizeof(vec4));
	srand(time(NULL));

 
	float cellSize = camera->tile_size;
	float scale = cellSize ;
	for(int i=0;i<model_cube->inst_cnt;i++)
 
	{
	 	int tiley = i / camera->tile_size ;
		int tilex = i % (int)camera->tile_size;

 
		glm_mat4_identity((vec4 *)&model_cube->m4_models[i]);
 
		float * color  ;
	
		float black [4]={0.0f,0.0f,0.0f,1.0f};
		float white [4]={1.0f,1.0f,1.0f,1.0f};

		color = white;
		

		model_cube_move_to_tile(&model_cube->insts[i], tilex, tiley);
	
		vec4 z = {scale,scale,scale,1.f};
		glm_scale((vec4 *)&model_cube->m4_models[i], z);

 

		glm_vec4_copy(color, (float *)&model_cube->v4_colors[i]);
 
		model_cube->insts[i].idx  = i;
 
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
	free(vdata);
 

	//--colors

	buffer_describe_vec4(model_cube->VBO_COL,GL_ARRAY_BUFFER, 1, 1);
	buffer_set_data(model_cube->VBO_COL,GL_ARRAY_BUFFER,model_cube->inst_cnt*sizeof(float[4]), model_cube->v4_colors, GL_DYNAMIC_DRAW);
 
	
 
 

	float * tdata;
	size_t tdata_len ;
 	wf_get_textcoord_data(wf, &tdata, &tdata_len);


	buffer_describe_vec2(model_cube->VBO_TEXTCOORD, GL_ARRAY_BUFFER, 0, 2);
	buffer_set_data(model_cube->VBO_TEXTCOORD, GL_ARRAY_BUFFER, tdata_len, tdata, GL_STATIC_DRAW);
	free(tdata);
	

	float * ndata;
	size_t ndata_len ;
 	wf_get_textcoord_data(wf, &ndata, &ndata_len);


	//normals 2*vec3 per triang
	//norm per vertex
	buffer_describe_vec3(model_cube->VBO_NORM,GL_ARRAY_BUFFER, 0, 3);
	buffer_set_data(model_cube->VBO_NORM,GL_ARRAY_BUFFER, ndata_len, ndata, GL_STATIC_DRAW);
	free(ndata);
 
///--- model matrix

	buffer_describe_mat4(model_cube->VBO_TRANSFORM, GL_ARRAY_BUFFER,1, 10);
	buffer_set_data(model_cube->VBO_TRANSFORM, GL_ARRAY_BUFFER, model_cube->inst_cnt*sizeof(float[16]), model_cube->m4_models, GL_DYNAMIC_DRAW);

	//unset data
 
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); 
 
 
	 
}
 

void model_cube_move_to_tile(Model_cube_inst p[static 1],int x,int y){

	Model_cube_inst inst = *p;
	inst.tilex = x;
	inst.tiley = y;


	float posx = x*camera->tile_size;
	float posy = y*camera->tile_size;
	vec4 v ={posx,posy,0.0f ,1.0f};
 
	
	glm_mat4_identity((vec4 *)&model_cube->m4_models[inst.idx]);
	glm_translate((vec4 *)&model_cube->m4_models[inst.idx],v);
	
 
	 
	*p = inst;
	
}

void model_cube_draw(Model_cube p [static 1]){
 
	glBindTexture(GL_TEXTURE_2D, p->texture01);
	glBindVertexArray(p->VAO);
	glDrawArraysInstanced(GL_TRIANGLES,0,max_sides*6,p->inst_cnt);

	
}
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