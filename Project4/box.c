#include "main.h"

//	geters and setters
t_v3d		ft_get_box_albedo(const void *data)
{
	return (((t_box*)data)->albedo);
}
t_v3d		ft_get_box_centr(const void *data)
{
	return (((t_box*)data)->centr);
}
t_rgb		ft_get_box_color(const void* data)
{
	return(((t_box*)data)->color);
}
void		ft_set_box_centr(t_box *box)
{
	box->centr.x = (box->min.x + box->max.x) / 2;
	box->centr.y = (box->min.y + box->max.y) / 2;
	box->centr.z = (box->min.z + box->max.z) / 2;
	box->size = vec_3magnitude(vec_3sub(box->max, box->min));
}
void		ft_set_min_max(t_box *box)
{
	box->min.x = box->centr.x - box->size;
	box->min.y = box->centr.y - box->size;
	box->min.z = box->centr.z - box->size;
	box->max.x = box->centr.x + box->size;
	box->max.y = box->centr.y + box->size;
	box->max.z = box->centr.z + box->size;
}

//	sphere intersect function
void		ft_fill_aabb_ray(const t_v3d *origin, const t_v3d *dir, t_aabb_ray *ray)
{
	ray->invdir.x = 1 / dir->x;
	ray->invdir.y = 1 / dir->y;
	ray->invdir.z = 1 / dir->z;
	ray->flag[0] = (ray->invdir.x < 0);
	ray->flag[1] = (ray->invdir.y < 0);
	ray->flag[2] = (ray->invdir.z < 0);
}
int8_t		ft_box_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t)
{
	t_aabb_ray	r;
	t_v3d		tmin;
	t_v3d		tmax;
	t_v3d		bounds[2];

	ft_fill_aabb_ray(orig, dir, &r);
	bounds[0] = ((t_box*)data)->cam_min;
	bounds[1] = ((t_box*)data)->cam_max;


	tmin.x = (bounds[r.flag[0]].x - orig->x) * r.invdir.x;
	tmax.x = (bounds[1 - r.flag[0]].x - orig->x) * r.invdir.x;

	tmin.y = (bounds[r.flag[1]].y - orig->y) * r.invdir.y;
	tmax.y = (bounds[1 - r.flag[1]].y - orig->y) * r.invdir.y;

	if ((tmin.x > tmax.y) || (tmin.y > tmax.x))
		return (false);

	tmin.x = (tmin.y > tmin.x) ? tmin.y : tmin.x;
	tmax.x = (tmax.y < tmax.x) ? tmax.y : tmax.x;

	tmin.z = (bounds[r.flag[2]].z - orig->z) * r.invdir.z;
	tmax.z = (bounds[1 - r.flag[2]].z - orig->z) * r.invdir.z;

	if ((tmin.x > tmax.z) || (tmin.z > tmax.x))
		return (false);

	tmin.x = (tmin.z > tmin.x) ? tmin.z : tmin.x;
	tmax.x = (tmax.z < tmax.x) ? tmax.z : tmax.x;

	*t = tmin.x;
	if (*t < 0) {
		*t = tmax.x;
		return (false);
	}
/*
	// 
	if (*t < 0) {
		*t = tmax.x;
		if (*t < 0) //when you do that you get intersection when the camera located in the box
			return false;
	}
*/
	return (true);
}
t_v3d		box_intersect_normals(const t_v3d *hit_point, const t_obj *obj_box)
{
	t_v3d	centr;
	t_v3d	normal;
	t_v3d	v;

	centr = obj_box->get_center(obj_box->data);
	normal = vec_1zero();
	v = vec_3sub(*hit_point, centr);
	//vec_3normalize(&v);
	if (fabs(v.x) >= fabs(v.y))
	{
		if (fabs(v.x) >= fabs(v.z))
			normal.x = (v.x > 0) ? 1 : -1;
		else
			normal.z = (v.z > 0) ? 1 : -1;
	}
	else
	{
		if (fabs(v.y) >= fabs(v.z))
			normal.y = (v.y > 0) ? 1 : -1;
		else
			normal.z = (v.z > 0) ? 1 : -1;
	}
	v = vec_3add(v, normal);
	vec_3normalize(&v);
	return (v);
}

//	constructor and destructor
void		ft_del_box(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}
int8_t		ft_mem_box(t_obj **obj, t_box **box)
{
	if ((*obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		return (false);
	if ((*box = (t_box*)malloc(sizeof(t_box))) == NULL)
	{
		free(*obj);
		return (false);
	}
	memset(*obj, 0, sizeof(t_obj));
	memset(*box, 0, sizeof(t_box));
	return (true);
}
t_obj*		ft_new_box(t_v3d *max, t_v3d *min, t_rgb color, double_t size)
{
	t_obj *obj;
	t_box *new_box;

	if ((ft_mem_box(&obj, &new_box)) == false || !max || size == 0.0)
		return (NULL);
	if (!min)
	{
		new_box->size = size;
		new_box->centr = *max;
		ft_set_min_max(new_box);
	}
	else
	{
		new_box->max = *max;
		new_box->min = *min;
		ft_set_box_centr(new_box);
	}

	new_box->color = color;
	new_box->albedo = vec_1double(0.18);
	obj->flag = box;
	obj->data = new_box;
	obj->get_albedo = ft_get_box_albedo;
	obj->get_color = ft_get_box_color;
	obj->get_center = ft_get_box_centr;
	obj->intersect = ft_box_intersect;
	obj->get_n_hit = box_intersect_normals;
	obj->next = NULL;
	return (obj);
}
