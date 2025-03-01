#pragma once

#include "cglm/affine.h"
#include <cglm/mat4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>


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
	 
 
}Model_floor;

extern void model_floor_init(Model_floor *ptr[static 1]);
extern void model_floor_free(Model_floor *ptr[static 1]);
extern void model_floor_draw(Model_floor ptr[static 1]);
extern void model_floor_update_shaders(Model_floor ptr[static 1]);
extern void model_floor_set_shader(Model_floor ptr[static 1],unsigned int shader_id);
//extern void model_floor_get_color(Model_floor ptr[static 1],int tilex,int tiley,float ** out);
extern bool model_color_cmp(float * a,float * b);

#ifdef MODEL_FLOOR_IMPLEMENTATION
 
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


 

static float colors[7][4] = {
	{0.5f,1.0f,0.2f,1.0f},
	{0.0f,0.0f,0.0f,1.0f},
	{1.0f,0.5f,0.2f,1.0f},
	{1.0f,1.0f,1.0f,1.0f},
	
	{0.2f,0.5f,1.0f,1.0f},
	{0.1f,1.0f,0.8f,1.0f},
	{0.1f,0.1f,0.5f,1.0f},
};

bool model_color_cmp(float * a,float * b){
	
	return (a[0] - b[0]) + (a[1] - b[1])+ (a[2] - b[2])+ (a[3] - b[3]) == 0;
}

// void model_floor_get_color(Model_floor ptr[static 1],int tilex,int tiley, float ** out){
// 	int pos = tiley * ptr->h + tilex;
// 	*out = colors[ptr->map2d[pos]];
// }
void model_floor_draw(Model_floor ptr[static 1]){
	glBindTexture(GL_TEXTURE_2D,ptr->texture01);
	glBindVertexArray(ptr->VAO);
	glDrawArraysInstanced(GL_TRIANGLES,0,6,ptr->num_inst);
}

void model_floor_init(Model_floor * ptr[static 1] ){
	if(*ptr != nullptr)
	{
		model_floor_free(ptr);
	}
	 
	*ptr =  calloc(1,sizeof(Model_floor));
	Model_floor *ref = (*ptr);
 
	// ref->w  = 32;
	// ref->h  = 32;
	ref->num_inst = 1;
 
 
	// File_s f_map = file_open("../assets/maps/32x32.bin", "rb");
	 
	// f_map.pfile_read(&f_map);
	// f_map.pfile_close(&f_map);
	// printf("ok ? %s %i %i\n",f_map.err,f_map.read_size,f_map.data_size);
	// ref->map2d = f_map.data;
	
	// Camera_s cam_inst = *((Camera_s *)game->camera);
	 
	glm_mat4_identity(ref->model);
	
	
	
	load_texture(&ref->texture01,"../assets/texture01.JPG");
 
	 
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

 
	struct {  size_t len; float * data;} vd,vt,vn;
	wf_get_vert_data(wf, &vd.data, &vd.len);

	wf_get_norm_data(wf, &vn.data, &vn.len);
	 
	wf_get_textcoord_data(wf, &vt.data, &vt.len);
 
 
	buffer_set_data(ref->VBO_VERT, GL_ARRAY_BUFFER, vd.len, vd.data, GL_STATIC_DRAW);
	

	vec4 col = {1.0f,1.0f,1.0f,1.0f};
	mat4 m ;
	glm_mat4_identity(m);
	glm_scale(m, (vec4){camera->tile_size*2 ,camera->tile_size*2 ,1.0f,1.0f});
	buffer_set_data(ref->VBO_COL, GL_ARRAY_BUFFER, sizeof(vec4) , col, GL_STATIC_DRAW);
	buffer_set_data(ref->VBO_TEXTCOORD, GL_ARRAY_BUFFER, vt.len, vt.data, GL_STATIC_DRAW);

	buffer_set_data(ref->VBO_NORM, GL_ARRAY_BUFFER, vn.len, vn.data, GL_STATIC_DRAW);
	buffer_set_data(ref->VBO_TRANSFORMS, GL_ARRAY_BUFFER, sizeof(mat4)  , m, GL_STATIC_DRAW);
	 
	free(vd.data);
	free(vt.data);
	free(vn.data);
	// int w = inst.w;
	// int h = inst.h;

 
	// for(int y =h-1;y>=0;y--){
	// 	for(int x =0;x<w;x++){

		 
	// 		int pos = y*h + x;
	// 		float *col = nullptr;
	// 		model_floor_get_color(&inst, x, y, &col);
	// 		buffer_set_subdata( inst.VBO_COL,GL_ARRAY_BUFFER, sizeof(float[4]),col, pos *sizeof(float[4]));
 
	// 		mat4 m ;
	// 		vec4 v;
	// 		v[0] = x * tile_size;
	// 		v[1] = y * tile_size;
	// 		v[2] = 0;
	// 		v[3] = 1;
	// 		glm_mat4_identity(m);
	// 		glm_translate(m, v);
		 
	// 		buffer_set_subdata( inst.VBO_TRANSFORMS,GL_ARRAY_BUFFER, sizeof(m),m, pos *sizeof(m));

	// 	}
	// 	*(*ptr) = inst;
	// }
 
 	
}
void model_floor_free(Model_floor  *ptr[static 1]){
	if(*ptr != nullptr)
	{	
		Model_floor *map = *ptr;
		// if(map->map2d!=nullptr)
		// {
		 
		// 	free(map->map2d);
		// }
		free(*ptr);
	}
	*ptr = nullptr;
}
#endif
