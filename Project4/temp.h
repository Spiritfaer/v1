#ifndef TEMP_H
#define TEMP_H

#include "struct.h"

void		ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size);
void		color_move(int *color, int up);
void		print_sdl(t_sdl *sdl);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		obj_info(const t_obj* obj);

void		fill_2(double_t **matrix, int32_t n);
void		fill_3(double_t **matrix, int32_t n);
void		fill_4(double_t **matrix, int32_t n);
void		fill_random_matrix(double_t **matrix, int32_t n);

double_t	get_dis(double_t a, double_t b, double_t c, double_t d);
void		print_matrix(double_t **matrix, int32_t n);
void		fs_swap(double_t *s, double_t *d);
void		set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b);
void		print_v3d(t_v3d *src, char *str);

#endif