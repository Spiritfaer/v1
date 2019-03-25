#include "main.h"

void	ft_del_box(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

int8_t	box_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t)
{
	t_box *box = data;

	
	box->tmin.x = (box->cam_min.x - orig->x) / dir->x;
	box->tmin.x = (box->cam_max.x - orig->x) / dir->x;

	if (box->tmin.x > box->tmax.x)
		fs_swap(&box->tmin.x, &box->tmax.x);

	box->tmin.y = (box->cam_min.y - orig->y) / dir->y;
	box->tmax.y = (box->cam_max.y - orig->y) / dir->y;

	if (box->tmin.y > box->tmax.y)
		fs_swap(&box->tmin.y, &box->tmax.y);

	if ((box->tmin.x > box->tmin.y) || (box->tmin.y > box->tmin.x))
		return (false);

	if (box->tmin.y > box->tmin.x)
		box->tmin.x = box->tmin.y;

	if (box->tmax.y < box->tmax.x)
		box->tmax.y = box->tmax.y;

	box->tmin.z = (box->cam_min.z - orig->z) / dir->z;
	box->tmax.z = (box->cam_max.z - orig->z) / dir->z;

	if (box->tmin.z > box->tmax.z)
		fs_swap(&box->tmin.z, &box->tmax.z);

	if ((box->tmin.x > box->tmax.z) || (box->tmin.z > box->tmax.x))
		return (false);

	if (box->tmin.z > box->tmin.x)
		box->tmin.x = box->tmin.z;

	if (box->tmax.z < box->tmax.x)
		box->tmax.x = box->tmax.z;

	return (true);
}

t_rgb	ft_get_box_color(const void* data)
{
	const t_box *temp;
	temp = data;
	return(temp->color);
}

t_obj*	ft_new_box(t_v3d *max, t_v3d *min, t_rgb color)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_box *new_box = (t_box*)malloc(sizeof(t_box));
	memset(new_box, 0, sizeof(t_box));

	obj->flag = box;
	new_box->color = color;

	new_box->max = *max;
	new_box->min = *min;

	obj->data = new_box;
	obj->get_color = ft_get_box_color;
	obj->intersect = box_intersect;
	obj->next = (void*)0;

	return (obj);
}
