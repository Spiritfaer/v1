#ifndef TEMP_H
#define TEMP_H

#include "struct.h"

void		ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size);
void		color_move(int *color, int up);
void		print_sdl(t_sdl *sdl);
void		*sf_memcpy(void *dst, const void *src, size_t n);
void		obj_info(const t_obj* obj);

double_t	get_dis(double_t a, double_t b, double_t c, double_t d);
void		print_matrix(double_t **matrix, int32_t n);
void		fs_double_swap(double_t *s, double_t *d);
void		set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b);
void		print_v3d(t_v3d *src, char *str);
void		print_v3i(t_v3i *src, char *str);

uint32_t	set_pixel_color(t_rgb color, double_t shadow);
uint32_t	set_pixel_color_with_hit_color(t_rgb color, t_hit *hit, t_light *light);

void		push_back_list(const char *line, t_list **des);
void		print_list(t_list *head);

int8_t		pars_file(const char *file_name, t_scena *scena);
int8_t		new_scena(const char *file_name, t_scena *scena);

#endif
