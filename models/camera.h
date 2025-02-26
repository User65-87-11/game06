#pragma once

 


 
typedef struct{
	float screen_w,screen_h;
 
	int tilex,tiley;
	float posx1,posy1;
	float mouse_x,mouse_y;
	float tile_size;
	unsigned int UBO;
 
	
 
	float* m4_projection;
	float* m4_view;
	float* m4_view_default;
	float* v3_view_pos;



}Camera_s;




void cam_move_to_tile(Camera_s cam[static 1],int,int);
void cam_screen_size(Camera_s cam[static 1],int,int);
void cam_init(Camera_s *cam[static 1]);
void cam_free(Camera_s *cam[static 1]);
 




#ifdef CAMERA_IMPLEMENTATION
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include "cglm/affine-post.h"
#include "cglm/affine-pre.h"
#include "cglm/affine.h"
#include "cglm/io.h"
#include "cglm/mat4.h"
#include "cglm/types.h"
#include "cglm/util.h"
#include "glm_wrap.h"
 

 

void  cam_init(Camera_s *cam[static 1]){
	cam_free(cam);
 
	//non dynamic mem camera
	 *cam=calloc(1, sizeof(Camera_s));
	 
	Camera_s inst = *(*cam);
	inst.tile_size = 16.0f;
	inst.m4_projection = calloc(1,sizeof(mat4) );
	inst.m4_view = calloc(1,sizeof(mat4) );
	inst.m4_view_default = calloc(1,sizeof(mat4));
	inst.v3_view_pos = calloc(1,sizeof(vec3));
	
	 
	//binding point 0
	glGenBuffers(1, &inst.UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, inst.UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4)*2, NULL, GL_STATIC_DRAW);  
	glBindBuffer(GL_UNIFORM_BUFFER, 0);




	*(*cam) =inst;
 
	 
}
 

void cam_free(Camera_s *cam[static 1]){
	if(*cam != nullptr){
		free((*cam)->m4_projection);
		free((*cam)->m4_view);
		free((*cam)->m4_view_default);
		free((*cam)->v3_view_pos);
		free(*cam);
		printf("free cam\n");
	
	}
}
 
void cam_screen_size(Camera_s cam[static 1],int w,int h){
	int z = max(w,h) * 2;
 
	Camera_s inst = *cam;
	inst.screen_h =  h;
	inst.screen_w =  w;
 
	glm_ortho(0, w, 0, h, -z, z, (vec4 *)inst.m4_projection);


	vec4 center ={w>>1,h>>1,0.f,1.f};
	glm_mat4_identity((vec4 *)inst.m4_view);
	glm_mat4_identity((vec4 *)inst.m4_view_default);
	glm_translate((vec4 *)inst.m4_view_default,center);
	glm_rotate_x((vec4 *)inst.m4_view_default, glm_rad(-60.0f), (vec4 *)inst.m4_view_default);
	glm_rotate_z((vec4 *)inst.m4_view_default, glm_rad(45.0f), (vec4 *)inst.m4_view_default);
	*cam =  inst;

	 
	glBindBuffer(GL_UNIFORM_BUFFER, inst.UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), inst.m4_projection);  
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), inst.m4_view_default);  
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	


	

	//cam_move_to_tile(cam,0,0);
	printf("cam_screen_size \n");
 
}

void cam_move_to_tile(Camera_s cam[static 1],int x,int y){
 
	
	Camera_s inst = *cam;
	float tsz =  inst.tile_size;
	inst.tilex = x;
	inst.tiley = y;
 
	inst.posx1 = (x )  * tsz;
	inst.posy1 = (y )  * tsz;

	inst.v3_view_pos[0] = inst.posx1;
	inst.v3_view_pos[1] = inst.posy1;
	inst.v3_view_pos[2] = 0.f ;
	
	glm_mat4_identity((vec4 *)inst.m4_view);

	glm_translate_to((vec4 *)inst.m4_view_default, inst.v3_view_pos,(vec4 *)inst.m4_view);
 
	
	*cam = inst;




	printf("cam pos: %i %i \n", inst.posx1, inst.posy1);
 
}
#endif