#pragma once






void game_mouse_handler(void* GLFWwindow, double xpos, double ypos);
static void game_key_handler(void* GLFWwindow, int key, int scancode, int action, int mods);
void game_framebuffer_size_handler(void* GLFWwindow, int width, int height);

void game_init();
void game_render();
void game_free();



typedef struct {
	void * camera ;
	void * model_cube ;
	void * model_floor ;
 
} Game;

Game * game;


#ifdef GAME_IMPLEMENTATION

static unsigned int shader_map;





#include <stdio.h>
 
#include <stdlib.h>

#include <GLFW/glfw3.h>
 

#include "../models/model_floor.h"

#include "../models/model_cube.h"

#include "../models/camera.h"

#include "keys.h"

#include "cglm/types.h"


#include "model_cube.h"
 
#include "camera.h"

typedef struct {
	Camera_s * camera ;
	Model_cube * model_cube ;
	Model_floor * model_floor ;

} Game_imp;

Game_imp * impl;
 
typedef  struct{
	int ids[];
} Shaderd_buffer;

 

void game_init(){
	impl = calloc(1,sizeof(Game));
	game = (Game *)impl;
 
 
 

	cam_init(&impl->camera);
	//45/5
 
	

	cam_move_to_tile(impl->camera, 0,0);
 
	shader_map = shader_compile(
		"../assets/shaders/model.map.vs.glsl", 
		"../assets/shaders/model.map.fs.glsl"
	);
 

	model_floor_init(&impl->model_floor);
	
	shader_use(shader_map);

	shader_bind_ubo("Matrices", impl->camera->UBO);
 
	shader_setMat4("model",impl->model_floor->model);
 
 
	model_cube_init(&impl->model_cube);

	keys_init();


 

}

 
void game_render(){

 

	shader_use(shader_map);
	model_floor_draw(impl->model_floor );
	 
 

	model_cube_draw(impl->model_cube);


 

}

 
static void game_key_handler(void * w, int key, int scancode, int action, int mods)
{
	GLFWwindow * window = w;
	if(impl==nullptr)return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	}else{
		keys_processInput(w);
	}

	 
}

void game_mouse_handler(void* w, double xpos, double ypos){
	GLFWwindow * window = w;
	if( impl == nullptr )return;
	impl->camera->mouse_x =  xpos;
	impl->camera->mouse_y =  ypos;
 

	
}
void game_framebuffer_size_handler(void* w, int width, int height)
{
	printf("game_framebuffer_size_handler\n");
	GLFWwindow * window = w;
	if(impl==nullptr)return;

	Camera_s *cam = impl->camera;

    glViewport(0, 0, width, height);
	cam_screen_size(cam, width, height);
 
	
	shader_use(shader_map);
	shader_setMat4("model", impl->model_floor->model);

	//model_update_shaders(model_cube);
	//model_2d_update_shaders(model_2d);
	 
}
void game_free(){
	if(impl!=nullptr)
	{
	 
		cam_free(&impl->camera);
		model_floor_free(&impl->model_floor);
		model_cube_free(&impl->model_cube);
		free(impl);
	}
	
}

#endif