//
// Created by User on 12.01.2019.
//

#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <crtdbg.h> 
#include "SDL.h"
#include "vmth.h"
#include "get_next_line.h"
#define _CRTDBG_MAP_ALLOC

#define CANVAS_SIZE 2

#define WIN_SIZE_W 640
#define WIN_SIZE_H 480

#define BG_COLOR 0xA3C6C0

#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF

#define MAX_DEPTH 5

#include "temp.h"
#include "struct.h"

enum e_bool {false, true};
enum e_ray_type {primary, shadow, ReflectionAndRefraction};

t_sdl		*ft_new_sdl(void);
void		ft_del_sdl(t_sdl *sdl);

int8_t		ft_init_sdl(t_sdl *sdl);
SDL_Surface *new_canvas(uint32_t width, uint32_t height);
//----------------------sphere()

t_obj*		ft_new_sphere(t_v3d centr, t_rgb color, double_t radius, double_t reflection);
void		ft_del_sphere(t_obj **obj);
int8_t		ft_sphere_intersect(t_ray *ray, const void *data, double_t *t);

t_rgb		ft_get_sphere_color(const void* data);
t_v3d		ft_get_center_sphere(void *data);
t_v3d		ft_get_sphere_albedo(const void *data);
t_v3d		ft_get_sphere_n_hit(const t_v3d *point_hit, const t_obj *obj);
double_t	ft_get_sphere_reflection(const void *data);
//----------------------plane()

t_obj*		ft_new_plane(t_v3d centr, t_rgb color, double_t radius, int32_t flag, double_t reflection);
int8_t		ft_plane_intersect(t_ray *ray, const void *data, double_t *t);

t_v3d		ft_get_center_plane(const void *data);
t_rgb		ft_get_plane_color(const void* data);
t_v3d		ft_get_plane_albedo(const void *data);
double_t	ft_get_plane_reflection(const void *data);
//------------------------box()

t_obj*		ft_new_box(t_v3d *max, t_v3d *min, t_rgb color, double_t size, double_t reflection);
void		ft_del_box(t_obj **obj);
int8_t		ft_box_intersect(t_ray *ray, const void *data, double_t *t);

t_rgb		ft_get_box_color(const void* data);
t_v3d		ft_get_box_centr(const void *data);
t_v3d		ft_get_box_albedo(const void *data);
t_v3d		ft_box_intersect_normals(const t_v3d *hit_point, const t_obj *obj_box);
double_t	ft_get_box_reflection(const void *data);
void		ft_set_box_centr(t_box *box);
void		ft_set_box_min_max(t_box *box);

//------------------------event

void		event_guard(t_sdl *sdl, t_camera *camera, t_time *time);
uint8_t		move_camera(const uint8_t *cur_key, t_matrix *camera, t_time *time);
void		time_tick(t_time *t);

//-------------------------render.c

void		ft_render(t_sdl *sdl, t_scena *scena);
void		refresh_obj(const t_matrix *camera, t_obj *obj, t_light *suns);
void		ft_draw(const t_sdl *sdl, t_scena *scena);
t_rgb		cast_ray(const t_sdl *sdl, t_scena *scena, t_ray *ray, int16_t depth);

//------------------------------

t_camera*	new_camera(t_v3d *pos, t_rgb *color, double_t fov);
void		destroy_camera(t_camera **camera);
t_light*	new_light(t_v3d *pos, t_rgb *color, double_t intensity);
t_v3d		get_to_light_dir(t_hit *hit, t_light *light);

//------------------------rgb()

t_rgb		get_black_color(void);
t_rgb		get_red_color(void);
t_rgb		get_green_color(void);
t_rgb		get_blue_color(void);
t_rgb		get_white_color(void);
void		set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b);
void		set_rgb_to_int(t_rgb *src);
void		set_int_to_rgb(t_rgb *src);
t_rgb		colort_add_colort(t_rgb one, t_rgb two);
t_rgb		colort_mult_f(t_rgb one, double_t f);
int32_t		colort_int_add_colort_int(int32_t one, int32_t two);

//-------------------------parser()

int8_t		new_scena(const char *file_name, t_scena *scena);
void		pars_type_obj(t_scena *scena);
int8_t		pars_info(t_list *list, t_rgb *color, t_v3d *pos, double_t *size);
int8_t		pars_size_fov_power(const char *str, double_t *src);
int8_t		pars_color(const char *str, t_rgb *color);
int8_t		pars_pos(const char *str, t_v3d *pos);
int8_t		pars_file(const char *file_name, t_scena *scena);

//-------------------------------

int8_t		ft_solve_quadratic(t_v3d *abc, t_v2d *tt);
t_obj*		ft_new_cone(t_v3d centr, t_rgb color, double_t radius);
#endif
