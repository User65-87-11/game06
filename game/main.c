 
#define MODEL_2D_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define FILE_IMPLEMENTATION
#define MODEL_CUBE_IMPLEMENTATION
#define MODEL_2D_IMPLEMENTATION
#define SHADER_IMPLEMENTATION
#define CAMERA_IMPLEMENTATION
#define MODEL_FLOOR_IMPLEMENTATION
#define KEYS_IMPLEMENTATIONS
#define GLFW_INCLUDE_NONE
#define BUFFER_IMPLEMENTATION
#define GAME_IMPLEMENTATION


#include "cglm/io.h"

#include <stdio.h>



#include <GLFW/glfw3.h>
#include <glad/gl.h>


#include <cglm/cglm.h>

 

#include "game.h"

#include "../models/model_floor.h"

#include "../models/model_cube.h"

#include "../models/camera.h"

#include "shader.h" // IWYU pragma: keep
#include "buffer.h"
 


static void error_callback(int error, const char* description);
static void mouse_callback(GLFWwindow * w, double xpos, double ypos);
static void framebuffer_size_callback(GLFWwindow * w,int width, int height);
static void key_callback(GLFWwindow * w, int key, int scancode, int action, int mods);

void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam);   

void processInput();

 

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
 
 extern Game * game;


// Model_cube * model_cube={};
// // Model_2d * model_2d={};
// Model_floor  *model_floor ={};
 

int main(){
	
 
	//--------
    glfwSetErrorCallback(error_callback); 

    if (!glfwInit())
		exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple example", NULL, NULL);
	
    if (!window)
    {
		
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	
	glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback( window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
       
        return -1;
    }

	glDebugMessageCallback(debug_callback,nullptr);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	glfwSwapInterval(1);


	game_init();

	framebuffer_size_callback(window,SCR_WIDTH,SCR_HEIGHT);
	// unsigned int shader_model_2d = shader_compile(
	// 	"../assets/shaders/model.2d.vs.glsl",
	// 	"../assets/shaders/model.2d.fs.glsl"
	// );
 
	// unsigned int shader_model_cube = shader_compile(
	// 	"../assets/shaders/model.cube.vs.glsl",
	// 	"../assets/shaders/model.cube.fs.glsl"
	// );
 



	// model_cube_init(&model_cube);
 
	// model_cube_move_to_tile(&(model_cube->insts[0]), 0, 0);
	
	// model_2d_init(&model_2d);

 
//	Model_2d_rect *rect  = &model_2d->rects[0];


	// model_rect_update_pos(rect,
	// 	(model_cube->insts[0].tilex )*camera->tile_size , 
	// 	(model_cube->insts[0].tiley  )*camera->tile_size
	// );
	// model_2d_update_shaders(model_2d);

	 
	float last_time =glfwGetTime();
	int fps_cnt =0;
	char buffer [50];

  
    while (!glfwWindowShouldClose(window)){
		float current_time = glfwGetTime();
		fps_cnt+=1;
 
 

		if( current_time - last_time > 1.0f)
		{

			last_time = current_time;
			snprintf(buffer, 50,"fps: %i \n", fps_cnt );
			glfwSetWindowTitle(window, buffer);
			
			fps_cnt = 0;
		}
	
		

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		


		game_render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		
    }
	
    glfwDestroyWindow(window);
 
    glfwTerminate();
	printf("exit ok");
	
	game_free();
    exit(EXIT_SUCCESS);


	return 0;
}



static void error_callback(int error, const char* description)
{
   
    printf("Error %i, %s\n",error,description);
}
 
static void mouse_callback(GLFWwindow * window, double xpos, double ypos){
	game_mouse_handler(window, xpos, ypos);
}
static void framebuffer_size_callback(GLFWwindow * window, int w, int  h){
	game_framebuffer_size_handler(window, w, h);
}
static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
	game_key_handler(window,   key,   scancode,   action,   mods);
}

void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam){
		
	printf("Opengl Error:\n");
	printf("Id: %i \n",id);
	printf("Type: %x \n",type);	
	printf("MSG: %s \n",message);	
}