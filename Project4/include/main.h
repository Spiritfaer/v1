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


#include "temp.h"
#include "struct.h"


t_sdl		*ft_new_sdl(void);
void		ft_del_sdl(t_sdl *sdl);

int8_t		ft_init_sdl(t_sdl *sdl);

//----------------------sphere()

t_obj*		ft_new_sphere(t_v3d centr, t_rgb color, double_t radius);
void		ft_del_sphere(t_obj **obj);

t_rgb		ft_get_sphere_color(const void* data);

int8_t		sphere_intersect(t_v3d *orig, t_v3d *dir, t_sphere *sphere, double_t *t);

//------------------------------

void		obj_info(const t_obj* obj);

//------------------------event

void	event_guard(t_sdl *sdl, t_camera *camera, t_time *time);
void	move_camera(uint8_t *cur_key, t_matrix *camera, t_time *time);
void	time_tick(t_time *t);

//------------------------------


#endif
