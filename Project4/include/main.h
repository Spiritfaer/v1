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

//------------------------------

void		obj_info(const t_obj* obj);

//------------------------matrix

double_t**	get_new_matrix(uint8_t n);
void		destroy_matrix(double_t **data, int32_t n);
void		fill_vertical_matrix(double_t **matrix, int32_t n);
void		print_matrix(double_t **matrix, int32_t n);
void		fill_random_matrix(double_t **matrix, int32_t n);
double_t**	invert_matrix(double_t **matrix, int32_t n);
double_t		get_discriminant(double_t **matrix, int32_t n);
double_t**		get_minors_matrix(double_t **src, int32_t size);
double_t**		get_copy_matryx(double_t **src, int32_t size);

//------------------------------


#endif
