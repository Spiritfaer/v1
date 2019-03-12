#include "main.h"

void	ft_del_sphere(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

uint8_t	ft_sphere_intersect(const int x, const int y, const t_sphere* my_sphere)
{
	//t_v2d center_proj;
	//t_v2d center_remap;
	//t_v2d center_pixel;


	//center_proj.x = my_sphere->centr.x / -my_sphere->centr.z;
	//center_proj.y = my_sphere->centr.y / -my_sphere->centr.z;

	//center_remap.x = (1 + center_proj.x) / 2;
	//center_remap.y = (1 + center_proj.y) / 2;

	//center_pixel.x = center_remap.x * 640;
	//center_pixel.y = center_remap.y * 480;

	//if (((x - center_pixel.x) * (x - center_pixel.x))
	//	+ ((y - center_pixel.y) * (y - center_pixel.y))
	//	< (my_sphere->radius * my_sphere->radius))
	//	return (1);
	if (((x - my_sphere->centr.x) * (x - my_sphere->centr.x))
		+ ((y - my_sphere->centr.y) * (y - my_sphere->centr.y))
		< (my_sphere->radius * my_sphere->radius))
		return (1);
	return (0);
}

t_rgb	ft_get_sphere_color(const void* data)
{
	const t_sphere *temp;
	temp = data;
	return(temp->color);
}

t_obj*	ft_new_sphere(t_v3d centr, t_rgb color, double_t radius)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_sphere *new_sphere = (t_sphere*)malloc(sizeof(t_sphere));

	ft_memcpy(&new_sphere->centr, &centr, sizeof(t_v3d));
	ft_memcpy(&new_sphere->color, &color, sizeof(t_rgb));

	obj->flag = sphere;
	new_sphere->radius = radius;
	new_sphere->centr = centr;
	new_sphere->color = color;

	obj->data = new_sphere;
	obj->get_color = ft_get_sphere_color;
	obj->intersect = ft_sphere_intersect;

	return (obj);
}
