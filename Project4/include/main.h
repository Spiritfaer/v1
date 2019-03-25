//
// Created by User on 12.01.2019.
//

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <crtdbg.h> 
#include "SDL.h"
#include "vmth.h"
#define _CRTDBG_MAP_ALLOC 

#define DISTANCE_TO_CANVAS 2
#define CANVAS_SIZE 2

#define WIN_SIZE_W 640
#define WIN_SIZE_H 480

#include "temp.h"
#include "struct.h"

enum e_bool {false, true};

t_sdl		*ft_new_sdl(void);
void		ft_del_sdl(t_sdl *sdl);

int8_t		ft_init_sdl(t_sdl *sdl);

//----------------------sphere()

t_obj*		ft_new_sphere(t_v3d centr, t_rgb color, double_t radius);
void		ft_del_sphere(t_obj **obj);

t_rgb		ft_get_sphere_color(const void* data);
t_v3d		get_center_sphere(void *data);
int8_t		sphere_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);

//----------------------plane()

t_obj*	ft_new_plane(t_v3d centr, t_rgb color, double_t radius, int32_t flag);
int8_t	plane_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);
t_v3d	get_center_plane(const void *data);
t_rgb	ft_get_plane_color(const void* data);


//------------------------------

void		obj_info(const t_obj* obj);
void		push_back_obj(t_obj *src, t_obj *des);

//------------------------event

void		event_guard(t_sdl *sdl, t_camera *camera, t_time *time);
uint8_t		move_camera(const uint8_t *cur_key, t_matrix *camera, t_time *time);
void		time_tick(t_time *t);

//------------------------------

t_camera*	make_camera(int32_t size);
void		destroy_camera(t_camera **camera);


#endif
