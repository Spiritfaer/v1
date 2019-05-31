#ifndef TEMP_H
#define TEMP_H

#include "struct.h"

//-----------------info()
void		print_v3d(const t_v3d *src, char *str);
void		print_v3i(const t_v3i *src, char *str);
void		ft_print_color(const t_rgb* color);
void		ft_print_plane(const void *data);
void		ft_print_sphere(const void *data);
void		ft_print_box(const void *data);
void		ft_print_cone(const void *data);
void		print_list(t_list *head);
void		print_matrix(double_t **matrix, int32_t n);
void		obj_info(const t_obj* obj);
void		print_sdl(t_sdl *sdl);

//----------------------tmp.c
void		ft_split_del(char **head);
void		push_back_list(const char *line, t_list **des);
void		push_back_light(t_light *src, t_light **des);
void		push_back_obj(t_obj *src, t_obj **des);

void		fs_double_swap(double_t *s, double_t *d);
uint32_t	set_pixel_color_with_hit_color(t_rgb color, t_hit *hit, t_light *light, t_ray *ray);
#endif
