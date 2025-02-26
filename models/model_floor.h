#pragma once

#include <cglm/mat4.h>
#include <cglm/cglm.h>
#include <cglm/types.h>


typedef struct {
	unsigned int w;
	unsigned int h;
	char   * map2d;
	unsigned int num_inst;
	unsigned int VAO,VBO[4];
 
	void * map_objects;
	mat4   model;
	 
 
}Model_floor;

void model_floor_init(Model_floor *ptr[static 1]);
void model_floor_free(Model_floor *ptr[static 1]);
void model_floor_draw(Model_floor ptr[static 1]);
void model_floor_update_shaders(Model_floor ptr[static 1]);
void model_floor_set_shader(Model_floor ptr[static 1],unsigned int shader_id);
void model_floor_get_color(Model_floor ptr[static 1],int tilex,int tiley,float ** out);
bool model_color_cmp(float * a,float * b);

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
#include "../game/game.h"
#include "camera.h"
#include "glm_wrap.h"

extern Game *game;

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

void model_floor_get_color(Model_floor ptr[static 1],int tilex,int tiley, float ** out){
	int pos = tiley * ptr->h + tilex;
	*out = colors[ptr->map2d[pos]];
}
void model_floor_draw(Model_floor ptr[static 1]){
	glBindVertexArray(ptr->VAO);
	glDrawArraysInstanced(GL_TRIANGLES,0,6,ptr->num_inst);
}

void model_floor_init(Model_floor * ptr[static 1] ){
	if(*ptr != nullptr)
	{
		model_floor_free(ptr);
	}
	 
	*ptr =  calloc(1,sizeof(Model_floor));
	Model_floor inst = *(*ptr);
	inst.w  = 32;
	inst.h  = 32;
	inst.num_inst = inst.h*inst.w;
 
 
	File_s f_map = file_open("../assets/maps/32x32.bin", "rb");
	 
	f_map.pfile_read(&f_map);
	f_map.pfile_close(&f_map);
	printf("ok ? %s %i %i\n",f_map.err,f_map.read_size,f_map.data_size);
	inst.map2d = f_map.data;
	
	Camera_s cam_inst = *((Camera_s *)game->camera);
	 
	glm_mat4_identity(inst.model);
	

 
	 
	glGenVertexArrays(1,&inst.VAO);
	glGenBuffers(4,inst.VBO);

	glBindVertexArray(inst.VAO);

 
	buffer_describe_vec3(inst.VBO[0], GL_ARRAY_BUFFER, 0, 0);
	buffer_describe_vec4(inst.VBO[1], GL_ARRAY_BUFFER, 1, 1);
	buffer_describe_vec2(inst.VBO[2], GL_ARRAY_BUFFER, 0, 2);
	buffer_describe_mat4(inst.VBO[3], GL_ARRAY_BUFFER, 1, 3);

 
 
	float cell_size = cam_inst.tile_size;

	float square[6][3]= {
		{0, 0, 0},
		{0, 0 + cell_size, 0},
		{0 + cell_size, 0 + cell_size, 0},
		{0 + cell_size, 0, 0},
		{0, 0, 0},
		{0 + cell_size, 0 + cell_size, 0},
	};
	buffer_set_data(inst.VBO[0], GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
	buffer_set_data(inst.VBO[1], GL_ARRAY_BUFFER, sizeof(vec4)  * inst.num_inst, nullptr, GL_STATIC_DRAW);
	buffer_set_data(inst.VBO[2], GL_ARRAY_BUFFER, sizeof(vec2)  , nullptr, GL_STATIC_DRAW);
	buffer_set_data(inst.VBO[3], GL_ARRAY_BUFFER, sizeof(mat4)  * inst.num_inst , nullptr, GL_STATIC_DRAW);
	 


	int w = inst.w;
	int h = inst.h;
	float tile_size = cam_inst.tile_size;
 
	for(int y =h-1;y>=0;y--){
		for(int x =0;x<w;x++){

		 
			int pos = y*h + x;
			float *col = nullptr;
			model_floor_get_color(&inst, x, y, &col);
			buffer_set_subdata( inst.VBO[1],GL_ARRAY_BUFFER, sizeof(float[4]),col, pos *sizeof(float[4]));
 
			mat4 m ;
			vec4 v;
			v[0] = x * tile_size;
			v[1] = y * tile_size;
			v[2] = 0;
			v[3] = 1;
			glm_mat4_identity(m);
			glm_translate(m, v);
		 
			buffer_set_subdata( inst.VBO[3],GL_ARRAY_BUFFER, sizeof(m),m, pos *sizeof(m));

		}
		*(*ptr) = inst;
	}
 
 	
}
void model_floor_free(Model_floor  *ptr[static 1]){
	if(*ptr != nullptr)
	{	
		Model_floor *map = *ptr;
		if(map->map2d!=nullptr)
		{
		 
			free(map->map2d);
		}
		free(*ptr);
	}
	*ptr = nullptr;
}
#endif
