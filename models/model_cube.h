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
	unsigned int VAO,VBO[5];
	unsigned int texture;
	size_t inst_cnt;
	Model_cube_inst  *insts ;

	 
	mat4 * m4_models ;
	vec4 * v4_colors  ;
  
} Model_cube;

 
void model_cube_free(Model_cube  *p [static 1]);
void model_cube_draw(Model_cube p [static 1]);
void model_cube_move_to_tile(Model_cube_inst p[static 1],int x,int y);
void model_cube_update_buffers(Model_cube p [static 1]);
void model_cube_init(Model_cube * ref[static 1]);
 

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
#include "stb_image.h"
#include "glm_wrap.h"
 
 
extern Camera_s *camera;
extern Model_floor * model_floor;
extern Model_cube * model_cube;


void load_texture(unsigned int * texture_id){
	 
	glGenTextures(1, texture_id);
	glBindTexture(GL_TEXTURE_2D, *texture_id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("../assets/img/texture_frame.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		if(nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf( "Failed to load texture\n" );
	}
	stbi_image_free(data);
}
void model_cube_init(Model_cube * ref[static 1]){
//	Camera_s * camera = game->camera;
	if(*ref)
	{
		model_cube_free(ref);
	}
	*ref = calloc(1,sizeof(Model_cube));
	
	//Model_cube model = *(*ref);
 
	 
	model_cube->inst_cnt = 1;

	if(model_cube->inst_cnt > model_floor->num_inst) 
	{
		model_cube->inst_cnt = model_floor->num_inst;
	}
	model_cube->insts = calloc(model_cube->inst_cnt,sizeof(Model_cube_inst) );
	model_cube->m4_models = malloc(model_cube->inst_cnt*sizeof(mat4));
	model_cube->v4_colors = malloc(model_cube->inst_cnt*sizeof(vec4));
	srand(time(NULL));

 
	 
	for(int i=0;i<model_cube->inst_cnt;i++)
 
	{
	 	int tiley = i / model_floor->h ;
		int tilex = i % model_floor->w ;

 
		glm_mat4_identity((vec4 *)&model_cube->m4_models[i]);
 
		float * color  ;
		model_floor_get_color(model_floor, tilex, tiley, &color);
		float black [4]={0.0f,0.0f,0.0f,1.0f};
		float white [4]={1.0f,1.0f,1.0f,1.0f};


		

		model_cube_move_to_tile(&model_cube->insts[i], tilex, tiley);


		if(model_color_cmp(color,black) || model_color_cmp(color,white))
		{
			vec4 z = {1.f,1.f,0.3f,1.f};
			if(model_color_cmp(color,white))
			{
				z[2] =0.0f;
			}
			color = z;
			glm_scale((vec4 *)&model_cube->m4_models[i], z);
			
		}

		glm_vec4_copy(color, (float *)&model_cube->v4_colors[i]);

		
		
		
		
		//glm_vec4_zero(model.insts[i].v4_color);
	 
		model_cube->insts[i].idx  = i;
 
	}

	
	
	constexpr int vsize = max_sides*6*3;
	constexpr int vert_cnt = max_sides*6;
	constexpr int triang_cnt = max_sides*2;
 

 
	//glm_mat4_identity((vec4 *)gl_inst.m4_base_model);
	
	int tw=32;
	int th=32;
	int outline_texture  [tw][th];
	memset(outline_texture,0, tw*th * sizeof(int));
 
	for(int i=2;i<tw-1;i++){
		outline_texture[2][i] = 0x000000ff;
		outline_texture[3][i] = 0x111111ff;
		outline_texture[5][i] = 0x111111ff;
		outline_texture[6][i] = 0x000000ff;
 
		outline_texture[tw-6][i] = 0x000000ff;
		outline_texture[tw-5][i] = 0x111111ff;
		outline_texture[tw-3][i] = 0x111111ff;
		outline_texture[tw-2][i] = 0x000000ff;

		outline_texture[i][tw-2] = 0x000000ff;
		outline_texture[i][tw-3] = 0x111111ff;
		outline_texture[i][tw-5] = 0x111111ff;
		outline_texture[i][tw-6] = 0x000000ff;
 

		outline_texture[i][2] = 0x000000ff;
		outline_texture[i][3] = 0x111111ff;
		outline_texture[i][5] = 0x111111ff;
		outline_texture[i][6] = 0x000000ff;

		
	}
	for(int i=4;i<tw-3;i++){

		outline_texture[4][i] = 0xFF0000ff;
		outline_texture[i][4] = 0xFF0000ff;
		outline_texture[i][tw-4] = 0xFF0000ff;
		outline_texture[tw-4][i] = 0xFF0000ff;
	}
	//load_texture(outline_texture);
 
 
	// float cube[vert_cnt][3] =
	// {
	// 	{0.0f,0.0f,0.0f},
	// 	{1.0f,0.0f,0.0f},
	// 	{1.0f,1.0f,0.0f},

	// 	{1.0f,1.0f,0.0f},
	// 	{0.0f,1.0f,0.0f},
	// 	{0.0f,0.0f,0.0f},

	// 	{0.0f,0.0f,1.0f},
	// 	{1.0f,0.0f,1.0f},
	// 	{1.0f,1.0f,1.0f},

	// 	{1.0f,1.0f,1.0f},
	// 	{0.0f,1.0f,1.0f},
	// 	{0.0f,0.0f,1.0f},

	// 	{0.0f,1.0f,1.0f},
	// 	{0.0f,1.0f,0.0f},
	// 	{0.0f,0.0f,0.0f},

	// 	{0.0f,0.0f,0.0f},
	// 	{0.0f,0.0f,1.0f},
	// 	{0.0f,1.0f,1.0f},

	// 	{1.0f,1.0f,1.0f},
	// 	{1.0f,1.0f,0.0f},
	// 	{1.0f,0.0f,0.0f},

	// 	{1.0f,0.0f,0.0f},
	// 	{1.0f,0.0f,1.0f},
	// 	{1.0f,1.0f,1.0f},

	// 	{0.0f,0.0f,0.0f},
	// 	{1.0f,0.0f,0.0f},
	// 	{1.0f,0.0f,1.0f},

	// 	{1.0f,0.0f,1.0f},
	// 	{0.0f,0.0f,1.0f},
	// 	{0.0f,0.0f,0.0f},

	// 	{0.0f,1.0f,0.0f},
	// 	{1.0f,1.0f,0.0f},
	// 	{1.0f,1.0f,1.0f},

	// 	{1.0f,1.0f,1.0f},
	// 	{0.0f,1.0f,1.0f},
	// 	{0.0f,1.0f,0.0f}	
	// }; 
	float cube[36][3] =
{
    {-1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},

    { 1.0f,  1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},

    {-1.0f, -1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},

    {-1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},

    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},

    { 1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},

    {-1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f,  1.0f},

    { 1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f, -1.0f},

    {-1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f, -1.0f}
};
	float cellSize = camera->tile_size;
 
	for(int i=0;i< vert_cnt ;i++ ){
		for(int j=0;j<3;j++)
		{
			cube[i][j] =cube[i][j] * cellSize;
		}
	}	
 
	glGenVertexArrays(1,&model_cube->VAO);
	glGenBuffers(5, model_cube->VBO);
 
 
	 
	//--
	glBindVertexArray( model_cube->VAO);
	
 
 
 

	buffer_describe_vec3(model_cube->VBO[0],GL_ARRAY_BUFFER, 0, 0);
	buffer_set_data(model_cube->VBO[0],GL_ARRAY_BUFFER, sizeof(cube),cube, GL_STATIC_DRAW);

 



	//--colors

	buffer_describe_vec4(model_cube->VBO[1],GL_ARRAY_BUFFER, 1, 1);
	buffer_set_data(model_cube->VBO[1],GL_ARRAY_BUFFER,model_cube->inst_cnt*sizeof(float[4]), model_cube->v4_colors, GL_DYNAMIC_DRAW);
 
	

	// //for (int i = 0; i < model.inst_cnt; i++) {
		
	// 	float * col =  (float*)model.v4_colors[i];
	 
	// 	buffer_set_subdata(model.VBO[1],GL_ARRAY_BUFFER,sizeof(float[4]),col,sizeof(float[4])*i);
	// }
	 
	 
	
 
	float texCoords[vert_cnt][2] = {
		// Front face
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},
	
		// Back face
		{1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},
		{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
	
		// Left face
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
	
		// Right face
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
	
		// Bottom face
		{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
		{1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},
	
		// Top face
		{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
		{1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}
	};
	
	buffer_describe_vec2(model_cube->VBO[2], GL_ARRAY_BUFFER, 0, 2);
	buffer_set_data(model_cube->VBO[2], GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	
	//normals 2*vec3 per triang
	//norm per vertex
	buffer_describe_vec3(model_cube->VBO[4],GL_ARRAY_BUFFER, 0, 7);
	buffer_set_data(model_cube->VBO[4],GL_ARRAY_BUFFER, sizeof(vec3)*vert_cnt, nullptr, GL_STATIC_DRAW);
	
	vec3 * norms = malloc(sizeof(vec3)*vert_cnt);
	for(int i=0;i<triang_cnt;i++)
	{
		int factor = i * 3;
		float * a = (float*) cube[factor ];
		float * b = (float*) cube[factor + 1];
		float * c = (float*) cube[factor + 2];

		vec3 u ,v ,n;

		glm_vec3_sub(a, b, u);
		glm_vec3_sub(a, c, v);
		glm_vec3_cross(u, v, n);
		glm_vec3_copy(n, norms[i]);
		glm_vec3_copy(n, norms[i + 1]);
		glm_vec3_copy(n, norms[i + 2]);
		
	}

///--- model matrix

	buffer_describe_mat4(model_cube->VBO[3], GL_ARRAY_BUFFER,1, 3);
	buffer_set_data(model_cube->VBO[3], GL_ARRAY_BUFFER, model_cube->inst_cnt*sizeof(float[16]), model_cube->m4_models, GL_DYNAMIC_DRAW);

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

// Create and bind an SSBO
GLuint ssbo;
glGenBuffers(1, &ssbo);
glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * dataSize, nullptr, GL_DYNAMIC_COPY);
glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

// Dispatch compute shader or render
glUseProgram(computeShaderProgram);
glDispatchCompute(workGroupsX, workGroupsY, workGroupsZ);
glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

// Map the buffer to CPU-accessible memory
glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
float* data = (float*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

// Read the data
for (int i = 0; i < dataSize; i++) {
    std::cout << data[i] << std::endl;
}

// Unmap the buffer
glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
*/

/**
UNIFORM BUFFERS
Switching between uniform buffer bindings is typically faster than switching dozens of uniforms in a program. Therefore, uniform buffers can be used to quickly change between different sets of uniform data for different objects that share the same program.
*/