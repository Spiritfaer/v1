#include "main.h"

void	ft_del_box(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

t_v3d	get_box_centr(const void *data)
{
	t_box *b = data;
	return (b->centr);
}

static void	set_box_centr(t_box *box)
{
	box->centr.x = (box->min.x + box->max.x) / 2;
	box->centr.y = (box->min.y + box->max.y) / 2;
	box->centr.z = (box->min.z + box->max.z) / 2;
	box->size = vec_3magnitude(vec_3sub(box->max, box->min));
}

static void set_min_max(t_box *box)
{
	box->min.x = box->centr.x - box->size;
	box->min.y = box->centr.y - box->size;
	box->min.z = box->centr.z - box->size;
	box->max.x = box->centr.x + box->size;
	box->max.y = box->centr.y + box->size;
	box->max.z = box->centr.z + box->size;
}

static void	fill_aabb_ray(const t_v3d *origin, const t_v3d *dir, t_aabb_ray *ray)
{
	ray->invdir.x = 1 / dir->x;
	ray->invdir.y = 1 / dir->y;
	ray->invdir.z = 1 / dir->z;
	ray->flag[0] = (ray->invdir.x < 0);
	ray->flag[1] = (ray->invdir.y < 0);
	ray->flag[2] = (ray->invdir.z < 0);
}

int8_t	box_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t)
{
	t_box		*box = data;
	t_aabb_ray	r;
	
	fill_aabb_ray(orig, dir, &r);
	box->bounds[0] = box->cam_min;
	box->bounds[1] = box->cam_max;

	
	box->tmin.x = (box->bounds[r.flag[0]].x - orig->x) * r.invdir.x;
	box->tmax.x = (box->bounds[1 - r.flag[0]].x - orig->x) * r.invdir.x;

	box->tmin.y = (box->bounds[r.flag[1]].y - orig->y) * r.invdir.y;
	box->tmax.y = (box->bounds[1 - r.flag[1]].y - orig->y) * r.invdir.y;

	if ((box->tmin.x > box->tmax.y) || (box->tmin.y > box->tmax.x))
		return (false);

	if (box->tmin.y > box->tmin.x)
		box->tmin.x = box->tmin.y;
	if (box->tmax.y < box->tmax.x)
		box->tmax.x = box->tmax.y;
	box->tmin.z = (box->bounds[r.flag[2]].z - orig->z) * r.invdir.z;
	box->tmax.z = (box->bounds[1 - r.flag[2]].y - orig->z) * r.invdir.z;

	if ((box->tmin.x > box->tmax.z) || (box->tmin.z > box->tmax.x))
		return (false);

	if (box->tmin.z > box->tmin.x)
		box->tmin.x = box->tmin.z;
	if (box->tmax.z > box->tmax.x)
		box->tmax.x = box->tmax.z;
	
	*t = box->tmin.x;

	if (*t < 0)
	{
		*t = box->tmax.x;
		if (*t < 0)
			return (false);
	}
	return (true);
}

t_rgb	ft_get_box_color(const void* data)
{
	const t_box *temp;
	temp = data;
	return(temp->color);
}

t_obj*	ft_new_box(t_v3d *max, t_v3d *min, t_rgb color, double_t size)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_box *new_box = (t_box*)malloc(sizeof(t_box));
	memset(new_box, 0, sizeof(t_box));

	obj->flag = box;
	new_box->color = color;

	if (!min)
	{
		new_box->size = size;
		new_box->centr = *max;
		set_min_max(new_box);
	}
	else
	{
		new_box->max = *max;
		new_box->min = *min;
		set_box_centr(new_box);
	}



	obj->data = new_box;
	obj->get_color = ft_get_box_color;
	obj->intersect = box_intersect;
	obj->get_center = get_box_centr;
	obj->next = NULL;

	return (obj);
}
