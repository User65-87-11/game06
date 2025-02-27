#pragma once


void keys_init();
void keys_press(int glKey);
void keys_release(int glKey);
bool keys_is_pressed(int glKey);
bool keys_is_released(int glKey);
void keys_processInput(void * win);
 
typedef struct  {
	unsigned int RELEASED;
	unsigned int PRESSED;
	unsigned int MASK;
}  ENUM_KEY_STATES ;

 
ENUM_KEY_STATES key_states_e={
	 .RELEASED = 1<<16,
	 .PRESSED = 2<<16,
	 .MASK = 0xffff0000
};
 
 

#define MAX_KEYS   350 
int gl_key[MAX_KEYS]={};



#ifdef KEYS_IMPLEMENTATIONS
#include <GLFW/glfw3.h>
#include <stdio.h>


#include "../models/camera.h"
#include "../models/model_cube.h"

#include "../models/model_2d.h"
#include "game.h"
 

extern Camera_s * camera ;

// extern Game * game; 
 

void keys_init(){
	for(int i=0;i<MAX_KEYS;i++)
	{
		gl_key[i] = i | key_states_e.RELEASED;
	}
}
void keys_press(int glKey)
{
	gl_key[glKey] = glKey | key_states_e.PRESSED;
	printf("keys_press: %i \n", glKey);
}
void keys_release(int glKey)
{
	gl_key[glKey] = glKey | key_states_e.RELEASED;
	//printf("keys_release: %i \n", glKey);
}
bool keys_is_pressed(int glKey)
{
	return (gl_key[glKey]  & key_states_e.MASK ) == key_states_e.PRESSED ;
}
bool keys_is_released(int glKey)
{
	return (gl_key[glKey]  & key_states_e.MASK ) == key_states_e.RELEASED ;
}
void keys_processInput(void * win)
{
	 

	GLFWwindow * window = win;
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{	

		if(keys_is_released(GLFW_KEY_W))
		{
			keys_press(GLFW_KEY_W);
			cam_move_to_tile(camera, camera->tilex , camera->tiley -1);

			// Model_cube_inst *inst = &model_cube->insts[0];
			// model_cube_move_to_tile(inst, inst->tilex  , inst->tiley + 1);

			// Model_2d_rect *rect  = &model_2d->rects[0];

			// model_2d_update_shaders(model_2d);
		}

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{	

		if(keys_is_released(GLFW_KEY_S))
		{
			keys_press(GLFW_KEY_S);
			cam_move_to_tile(camera, camera->tilex , camera->tiley +1);
			
			// Model_cube_inst *inst = &model_cube->insts[0];
			// model_cube_move_to_tile(inst, inst->tilex  , inst->tiley - 1);

			// Model_2d_rect *rect  = &model_2d->rects[0];
	 
			// model_2d_update_shaders(model_2d);
		}

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{	

		if(keys_is_released(GLFW_KEY_A))
		{
			keys_press(GLFW_KEY_A);
			cam_move_to_tile(camera, camera->tilex + 1 , camera->tiley );

			// Model_cube_inst *inst = &model_cube->insts[0];
			// model_cube_move_to_tile(inst, inst->tilex - 1, inst->tiley);

		 
			// Model_2d_rect *rect  = &model_2d->rects[0];
			 
			// model_2d_update_shaders(model_2d);
		}

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{	

		if(keys_is_released(GLFW_KEY_D))
		{
			keys_press(GLFW_KEY_D);
			cam_move_to_tile(camera, camera->tilex - 1 , camera->tiley );

			// Model_cube_inst *inst = &model_cube->insts[0];
			// model_cube_move_to_tile(inst, inst->tilex + 1, inst->tiley);


			 
			// Model_2d_rect *rect  = &model_2d->rects[0];
		 
			// model_2d_update_shaders(model_2d);
		}


	}
 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{	
		keys_release(GLFW_KEY_W);
	}
 
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{	
		keys_release(GLFW_KEY_S);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
	{	
		keys_release(GLFW_KEY_A);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{	
		keys_release(GLFW_KEY_D);
	}
 
}

#endif