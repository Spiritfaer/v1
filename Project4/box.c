#include "main.h"

t_v3d	get_center_box(const void *data)
{
	const t_box *s = data;
	return(s->cam_centr);
}

void	ft_del_box(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

int8_t box_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t)
{
	return (false);
}

t_rgb	ft_get_box_color(const void* data)
{
	const t_box *temp;
	temp = data;
	return(temp->color);
}

t_obj*	ft_new_box(t_v3d centr, t_rgb color, double_t radius, t_v3d *max, t_v3d *min)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_box *new_box = (t_box*)malloc(sizeof(t_box));

	ft_memcpy(&new_box->world_centr, &centr, sizeof(t_v3d));
	ft_memcpy(&new_box->color, &color, sizeof(t_rgb));

	obj->flag = box;
	new_box->size = radius;
	new_box->world_centr = centr;
	new_box->color = color;

	new_box->max = *max;
	new_box->min = *min;


	obj->data = new_box;
	obj->get_color = ft_get_box_color;
	obj->intersect = box_intersect;
	obj->get_center = get_center_box;
	obj->next = NULL;

	return (obj);
}
