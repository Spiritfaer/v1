#ifndef TEMP_H
#define TEMP_H

#include "struct.h"

void	ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size);
void	color_move(int *color, int up);
void	print_sdl(t_sdl *sdl);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	obj_info(const t_obj* obj);

#endif