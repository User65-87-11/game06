#pragma once
 

#include "camera.h"
#include "cglm/mat4.h"
#include "cglm/types.h"
#include "glmath.h"
typedef struct {

	// float x;
	// float y;
	// float w;
	// float h;
	
	float x;
	float y;
	float w;
	float h;
	 

}Model_2d_rect;

typedef struct{
	int num_inst;
	unsigned int VAO,VBO[2],SHADER_ID;
	Model_2d_rect * rects;
	

}Model_2d;

void model_2d_free(Model_2d * m[static 1]);
void model_2d_init(Model_2d * m[static 1]);
void model_2d_update_buffers(Model_2d m[static 1]);
void model_2d_update_shaders(Model_2d m[static 1]);
void model_2d_render(Model_2d m[static 1]);
void model_rect_update_size(Model_2d_rect[static 1],float w,float h);
void model_rect_update_pos( Model_2d_rect[static 1],float x,float y);
void model_2d_set_shader( Model_2d[static 1],unsigned int shader_id);


#ifdef MODEL_2D_IMPLEMENTATION

#include "cglm/io.h"
#include <stdio.h>
#include <stdlib.h>
#include "../game/shader.h"
//#include "camera.h"
#include "model_floor.h"
#include "glm_wrap.h"


extern Camera_s *camera;
 
 
void model_2d_set_shader( Model_2d model[static 1],unsigned int shader_id){
	model->SHADER_ID = shader_id;
}
void model_rect_update_pos(Model_2d_rect rect[static 1],float x,float y){
	
 
	rect->x = x;
	rect->y = y;
	
}
void model_rect_update_size(Model_2d_rect rect[static 1],float w,float h){
	printf("new size %f %f\n",w,h);
	
	rect->w= w;
	rect->h = h;
	
}
void model_rect_base_vert(Model_2d_rect  rect[static 1], float * v6x2){
	Model_2d_rect inst = *rect;
 
	float x1 = inst.x ;
	float y1 = inst.y ;
	float x2 = x1 + inst.w;
	float y2 = y1 + inst.h;

	float (*out)[2] = (float (*)[2])v6x2;
	out[0][0] = x1;	out[0][1] = y1;
	out[1][0] = x1;	out[1][1] = y2;
	out[2][0] = x2;	out[2][1] = y2;
	out[3][0] = x2;	out[3][1] = y1;
	out[4][0] = x1;	out[4][1] = y1;
	out[5][0] = x2;	out[5][1] = y2;
}	

void model_2d_init(Model_2d * m[static 1]){
 
	if((*m)!= nullptr){
		
		model_2d_free(m);
	}

	(*m) = calloc(1, sizeof(Model_2d));
 
	Model_2d inst = *(*m);
	 
	inst.num_inst = 5;
	inst.rects = calloc(1,sizeof(Model_2d_rect) *inst.num_inst);
	 
	for(int i=0;i<inst.num_inst;i++)
	{
 
		model_rect_update_size(&inst.rects[i],camera->tile_size,camera->tile_size);
		
	}
 
	glCreateVertexArrays(1,&inst.VAO);
	glCreateBuffers(2,inst.VBO);

	glBindVertexArray(inst.VAO);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[0]);
	glVertexAttribPointer(0,  2, GL_FLOAT, GL_FALSE,   sizeof(float) * 2, 0);
	 
	float pos [inst.num_inst][6][2]={};
	for(int i=0;i<inst.num_inst;i++)
	{
		
		model_rect_base_vert(&inst.rects[i], (float *)&pos[i]);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos) ,pos, GL_DYNAMIC_DRAW); 


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);


	//--
		 
	
 
	*(*m) = inst;
}
void model_2d_render(Model_2d m[static 1]){
	
	shader_use(m->SHADER_ID);
	//shader_setMat4("view_pos", camera->m4_view);

	glBindVertexArray(m->VAO);
	glDrawArrays(GL_TRIANGLES,0,6*m->num_inst);
}
void model_2d_update_buffers(Model_2d m[static 1]){

	float pos [m->num_inst][6][2]={};
	for(int i=0;i<m->num_inst;i++)
	{
		
		model_rect_base_vert(&m->rects[i], (float *)&pos[i]);
	}

	glBindBuffer(GL_ARRAY_BUFFER,m->VBO[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(pos) , pos); 
}
void model_2d_update_shaders(Model_2d m[static 1]){
 
 
	vec4 v ={};
	v[0] = m->rects[0].x;
	v[1] = m->rects[0].y;
	v[3] = 1.0;//positional
 
 
	float vecs[6][4] ={} ;

	model_rect_base_vert(&m->rects[0], (float *)vecs);
	vecs[0][3] = 1.0f;
	vecs[1][3] = 1.0f;
	vecs[2][3] = 1.0f;
	vecs[3][3] = 1.0f;
	vecs[4][3] = 1.0f;
	vecs[5][3] = 1.0f;
 
	float x=10000.f,y=10000.f; 
	for(int i=0;i <6 ;i++){
		printf("v x:%f y:%f\n",vecs[i][0],vecs[i][1]);
		glm_mat4_mulv((vec4 *)camera->m4_view_default, vecs[i], vecs[i]);
		
		
		if(vecs[i][0] < x)
		{
			x = vecs[i][0];
		}
		if(vecs[i][1] < y)
		{
			y = vecs[i][1];
		}
	}
	
	 
	model_rect_update_pos(&m->rects[0], x, y) ;
	
	model_2d_update_buffers(m);
 
	shader_use(m->SHADER_ID);
	shader_setVec3("view_pos", v);
 
}
void model_2d_free(Model_2d * m[static 1]){
	if((*m)!= nullptr)
	{
	 
		free((*m)->rects);
	}
	(*m) = nullptr;
}
#endif