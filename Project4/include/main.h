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
SDL_Surface *new_canvas(uint32_t width, uint32_t height);
//----------------------sphere()

t_obj*		ft_new_sphere(t_v3d centr, t_rgb color, double_t radius);
void		ft_del_sphere(t_obj **obj);

t_rgb		ft_get_sphere_color(const void* data);
t_v3d		ft_get_center_sphere(void *data);
int8_t		ft_sphere_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);
t_v3d		ft_get_sphere_albedo(const void *data);
t_v3d		ft_get_sphere_n_hit(const t_v3d *point_hit, const t_obj *obj);

//----------------------plane()

t_obj*		ft_new_plane(t_v3d centr, t_rgb color, double_t radius, int32_t flag);
int8_t		plane_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);
t_v3d		get_center_plane(const void *data);
t_rgb		ft_get_plane_color(const void* data);
t_v3d		get_plane_albedo(const void *data);

//------------------------box()

t_obj*		ft_new_box(t_v3d *max, t_v3d *min, t_rgb color, double_t size);
t_rgb		ft_get_box_color(const void* data);
int8_t		ft_box_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);
void		ft_del_box(t_obj **obj);
t_v3d		ft_get_box_centr(const void *data);
void		ft_set_box_centr(t_box *box);
void		ft_set_min_max(t_box *box);
t_v3d		ft_get_box_albedo(const void *data);

//------------------------------

void		obj_info(const t_obj* obj);
void		push_back_obj(t_obj *src, t_obj *des);

//------------------------event

void		event_guard(t_sdl *sdl, t_camera *camera, t_time *time);
uint8_t		move_camera(const uint8_t *cur_key, t_matrix *camera, t_time *time);
void		time_tick(t_time *t);


//-------------------------render.c

void		ft_render(t_sdl *sdl, t_obj *obj, t_light *suns);
void		refresh_obj(const t_matrix *camera, t_obj *obj, t_light *suns);
void		ft_draw(const t_sdl *sdl, SDL_Surface *canvas, const t_obj *obj, t_camera *camera, t_light *suns);
uint8_t		cast_ray(const t_sdl *sdl, const t_obj *obj, t_v3d *orig, t_v3d *dir, t_v2i i, SDL_Surface *canvas, t_light *suns);

//------------------------------

t_camera*	make_camera(int32_t size);
void		destroy_camera(t_camera **camera);
t_light*	new_light(t_v3d *pos, t_rgb *color, double_t intensity);

#endif
