#pragma once

#include "cglm/affine-pre.h"
#include "cglm/affine.h"
#include "cglm/util.h"
#include <cglm/mat4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>

typedef struct WF WF;

typedef struct {
	// unsigned int w;
	// unsigned int h;
	//char   * map2d;
	unsigned int num_inst;
	unsigned int VAO;
	unsigned int VBO_TEXTCOORD,VBO_COL,VBO_VERT,VBO_NORM,VBO_TRANSFORMS;
	//void * map_objects;
	unsigned int texture01;
	mat4   model;
	WF * wf;
	 
 
}Model_plane;

extern void model_plane_init(Model_plane *ptr[static 1]);
extern void model_plane_free(Model_plane *ptr[static 1]);
extern void model_plane_draw(Model_plane ptr[static 1]);
extern void model_plane_contains(Model_plane ptr[static 1], float x,float y);
 
 

#ifdef MODEL_PLANE_IMPLEMENTATION
 
#include <math.h>
#include <cglm/mat4.h>
#include <cglm/vec4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>
#include <glad/gl.h>
#include <stdio.h>
#include <stdlib.h>


#include "file/file.h"

#include "../game/shader.h"
#include "../game/buffer.h"
#include "../game/wavefront.h"
#include "../game/wavefront.h"
#include "../game/game.h"
#include "../game/load_texture.h"

#include "camera.h"
#include "glm_wrap.h"


extern Camera_s *camera;


 

 
 
// void model_plane_contains(Model_plane ptr[static 1], float x,float y){
// 	mat4 pv ; 
// 	glm_mat4_mul(camera->m4_projection, camera->m4_view, pv);
 
	 
// 		for(int i=0;i<ptr.wf->attrib.num_vertices;i++)
// 		{
// 			float *v3 = &ptr.wf->attrib.vertices[i*3];
// 			vec4 vert;
// 			vert[3] = 1.0f;
// 			vert[0] = v3[0];
// 			vert[1] = v3[1];
// 			vert[2] = v3[2];
// 			vec4 temp ;
// 			glm_mat4_mulv(ptr->model, vert, temp);
// 			glm_mat4_mulv(pv, temp, temp);

// 		}
		
	 
// }
void model_plane_draw(Model_plane ptr[static 1]){
	glBindTexture(GL_TEXTURE_2D,ptr->texture01);
	glBindVertexArray(ptr->VAO);
	glDrawArraysInstanced(GL_TRIANGLES,0,6,ptr->num_inst);
}

void model_plane_init(Model_plane * ptr[static 1] ){
	if(*ptr != nullptr)
	{
		model_plane_free(ptr);
	}
	 
	*ptr =  calloc(1,sizeof(Model_plane));
	Model_plane *ref = (*ptr);
 
 
	ref->num_inst = 1;
 
 
 
	 
	glm_mat4_identity(ref->model);
	
	
	
	load_texture(&ref->texture01,"../assets/DSC_2583.png");
 
	 
	glGenVertexArrays(1,&ref->VAO);
	glGenBuffers(1,&ref->VBO_COL);
	glGenBuffers(1,&ref->VBO_NORM);
	glGenBuffers(1,&ref->VBO_TEXTCOORD);
	glGenBuffers(1,&ref->VBO_VERT);
	glGenBuffers(1,&ref->VBO_TRANSFORMS);

	glBindVertexArray(ref->VAO);

 
	buffer_describe_vec3(ref->VBO_VERT, GL_ARRAY_BUFFER, 0, 0);
	buffer_describe_vec4(ref->VBO_COL, GL_ARRAY_BUFFER, 1, 1);
	buffer_describe_vec2(ref->VBO_TEXTCOORD, GL_ARRAY_BUFFER, 0, 2);
	buffer_describe_vec3(ref->VBO_NORM, GL_ARRAY_BUFFER, 0, 3);
	buffer_describe_mat4(ref->VBO_TRANSFORMS, GL_ARRAY_BUFFER, 1, 10);

	
	WF *wf;
	wf_load(&wf, "../assets/models/mesh_plane01_yz.obj");

	ref->wf = wf;
 
	struct {  size_t len; float * data;} vd,vt,vn;
	wf_get_vert_data(wf, &vd.data, &vd.len);

	wf_get_norm_data(wf, &vn.data, &vn.len);
	 
	wf_get_textcoord_data(wf, &vt.data, &vt.len);
 
 
	buffer_set_data(ref->VBO_VERT, GL_ARRAY_BUFFER, vd.len, vd.data, GL_STATIC_DRAW);
	

	vec4 col = {1.0f,1.0f,1.0f,1.0f};
	 
 
	glm_scale(ref->model, (vec4){camera->tile_size*5 ,camera->tile_size*5 ,1.0f,1.0f});
	glm_rotate_y(ref->model, glm_rad(45), ref->model);

	buffer_set_data(ref->VBO_COL, GL_ARRAY_BUFFER, sizeof(vec4) , col, GL_STATIC_DRAW);
	buffer_set_data(ref->VBO_TEXTCOORD, GL_ARRAY_BUFFER, vt.len, vt.data, GL_STATIC_DRAW);

	buffer_set_data(ref->VBO_NORM, GL_ARRAY_BUFFER, vn.len, vn.data, GL_STATIC_DRAW);

	buffer_set_data(ref->VBO_TRANSFORMS, 
		GL_ARRAY_BUFFER, 
		sizeof(mat4), 
		ref->model, 
		GL_STATIC_DRAW
	);
	 
	free(vd.data);
	free(vt.data);
	free(vn.data);

	 
 	
}
void model_plane_free(Model_plane  *ptr[static 1]){
	if(*ptr != nullptr)
	{	
 
		free((*ptr)->wf);
		free(*ptr);
	}
	*ptr = nullptr;
}
#endif
