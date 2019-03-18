#include "main.h"

void	ft_del_sphere(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

uint8_t	ft_sphere_intersect(const t_v2i i, const t_sphere* my_sphere)
{

	t_v2d	p_screen;
	t_v2d	p_ndc;
	t_v2i	p_raster;

	double_t canvasWidth = 2;
	double_t canvasHeight = 2;
	//t_v2d center_pixel;


	p_screen.x = my_sphere->cam_centr.x / -my_sphere->cam_centr.z;
	p_screen.y = my_sphere->cam_centr.y / -my_sphere->cam_centr.z;

	p_ndc.x = (p_screen.x + canvasWidth * 0.5) / canvasWidth;
	p_ndc.y = (p_screen.y + canvasHeight * 0.5) / canvasHeight;

	p_raster.x = (int)(p_ndc.x * 640);
	p_raster.y = (int)((1 - p_ndc.y) * 480);

	//center_remap.x = (1 + center_proj.x) / 2;
	//center_remap.y = (1 + center_proj.y) / 2;

	//center_pixel.x = center_remap.x * 640;
	//center_pixel.y = center_remap.y * 480;

	//if (((x - center_pixel.x) * (x - center_pixel.x))
	//	+ ((y - center_pixel.y) * (y - center_pixel.y))
	//	< (my_sphere->radius * my_sphere->radius))
	//	return (1);
	if (((i.x - p_raster.x) * (i.x - p_raster.x))
		+ ((i.y - p_raster.y) * (i.y - p_raster.y))
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

	ft_memcpy(&new_sphere->world_centr, &centr, sizeof(t_v3d));
	ft_memcpy(&new_sphere->color, &color, sizeof(t_rgb));

	obj->flag = sphere;
	new_sphere->radius = radius;
	new_sphere->world_centr = centr;
	new_sphere->color = color;

	obj->data = new_sphere;
	obj->get_color = ft_get_sphere_color;
	obj->intersect = ft_sphere_intersect;

	return (obj);
}
