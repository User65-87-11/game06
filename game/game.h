#pragma once






#include "buffer.h"
void game_mouse_handler(void* GLFWwindow, double xpos, double ypos);
static void game_key_handler(void* GLFWwindow, int key, int scancode, int action, int mods);
void game_framebuffer_size_handler(void* GLFWwindow, int width, int height);

void game_init();
void game_render();
void game_free();



// typedef struct {
// 	void * camera ;
// 	void * model_cube ;
// 	void * model_floor ;
 
// } Game;

// Game * game;


#ifdef GAME_IMPLEMENTATION

static unsigned int shader_map;

static unsigned int shader_id;



#include <stdio.h>
 
#include <stdlib.h>

#include <GLFW/glfw3.h>
 


#include "../models/model_floor.h"


#include "../models/model_cube.h"


#include "../models/camera.h"

#include "keys.h"

#include "cglm/types.h"


#include "model_cube.h"
 
//#include "camera.h"

// typedef struct {
// 	Camera_s * camera ;
// 	Model_cube * model_cube ;
// 	Model_floor * model_floor ;

// } Game_imp;


void game_texture_buffer_init();

Camera_s * camera ;
Model_cube * model_cube ;
Model_floor * model_floor ;

// Game_imp * impl;
 
 


unsigned int fb_texture =0;
unsigned int framebuffer;

void game_init(){
 
 
 

	cam_init(&camera);
	//45/5
 
	

	cam_move_to_tile(camera, 0,0);
 
	shader_map = shader_compile(
		"../assets/shaders/model.map.vs.glsl", 
		"../assets/shaders/model.map.fs.glsl"
	);
 
	shader_id = shader_compile(
		"../assets/shaders/model.id.vs.glsl", 
		"../assets/shaders/model.id.fs.glsl"
	);
 

	shader_use(shader_map);

	shader_bind_ubo("Matrices", camera->UBO);

	
	shader_use(shader_id);

	shader_bind_ubo("Matrices", camera->UBO);

	

	model_floor_init(&model_floor);

 
	model_cube_init(&model_cube);

	keys_init();



	glGenFramebuffers(1, &framebuffer);
	

 

}

int prev_color = 0;
static void print_pixel(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
 

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Clear to blue (example)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	shader_use(shader_id);


	{
		 
		glBindVertexArray(model_cube->VAO_ID);
		glDrawArraysInstanced(GL_TRIANGLES,0,max_sides*6,model_cube->inst_cnt);
	}


	//--
	unsigned char data[4] ;
	int *idata = (int *)data;
	glReadPixels(camera->mouse_x,camera->mouse_y, 1, 1,GL_RGBA, GL_UNSIGNED_BYTE, &data);
	if(prev_color != *idata)
	{	
		prev_color = *idata;
		for(int i=0;i<model_cube->inst_cnt;i++)
		{
			
			float * col = (float*)&model_cube->v4_colors[i];
			col[1] = 1.0f;
			col[2] = 1.0f;
			//printf("was:%x, got:%x \n",model_cube->insts[i].ID,prev_color);
			if(model_cube->insts[i].ID == prev_color)
			{
				printf("ID ok: r:%02x g:%02x b:%02x a:%02x\n",data[0],data[1],data[2],data[3]);
				col[1] = 0.0f;
				col[2] = 0.0f;
			}
		}
		
		// printf("ID ok: r:%02x g:%02x b:%02x a:%02x int:%i \n",data[0],data[1],data[2],data[3],prev_color);
		
		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
 
void game_render(){

 
	print_pixel();
	//
 

	glClearColor(0.6f, 0.2f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	



	shader_use(shader_map);
	model_floor_draw(model_floor );

 

	{
	 
		glBindTexture(GL_TEXTURE_2D, model_cube->texture01);
		glBindVertexArray(model_cube->VAO);

		 
		buffer_set_subdata(model_cube->VBO_COL,
			GL_ARRAY_BUFFER,
			model_cube->inst_cnt*sizeof(vec4),
			model_cube->v4_colors,
			0);

		glDrawArraysInstanced(GL_TRIANGLES,0,max_sides*6,model_cube->inst_cnt);
	}

	
 

}

 
static void game_key_handler(void * w, int key, int scancode, int action, int mods)
{
	GLFWwindow * window = w;
	 

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	}else{
		keys_processInput(w);
	}

	 
}
 
void game_mouse_handler(void* w, double xpos, double ypos){
	// 0.01
 
	GLFWwindow * window = w;
 
	camera->mouse_x =  xpos;
	camera->mouse_y =  camera->screen_h -  ypos;
 
	
	
}
void game_framebuffer_size_handler(void* w, int width, int height)
{
	printf("game_framebuffer_size_handler\n");
	GLFWwindow * window = w;
	 

	Camera_s *cam = camera;

    glViewport(0, 0, width, height);
	cam_screen_size(cam, width, height);
 
	
	//shader_use(shader_map);
 

	//model_update_shaders(model_cube);
	//model_2d_update_shaders(model_2d);


	game_texture_buffer_init();
	 
}
void game_free(){
	 
	{
	 
		cam_free(&camera);
		model_floor_free(&model_floor);
		model_cube_free(&model_cube);
		glDeleteTextures(1,&fb_texture);
		glDeleteFramebuffers(1, &framebuffer);
	 
	}
	
}
void game_texture_buffer_init(){
	//--
	if(fb_texture!=0)
	{
		glDeleteTextures(1, &fb_texture);
	}
	
	glGenTextures(1, &fb_texture);
    glBindTexture(GL_TEXTURE_2D, fb_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, camera->screen_w, camera->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Generate framebuffer
  
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_texture, 0);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB not complete!\n");
        exit(-1);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#endif