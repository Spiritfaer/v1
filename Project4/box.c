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
double_t	ft_get_box_reflection(const void *data)
{
	return (((t_box*)data)->reflection);
}
void		ft_set_box_centr(t_box *box)
{
	box->centr.x = (box->min.x + box->max.x) / 2;
	box->centr.y = (box->min.y + box->max.y) / 2;
	box->centr.z = (box->min.z + box->max.z) / 2;
	box->size = vec_3magnitude(vec_3sub(box->max, box->min));
}
void		ft_set_box_min_max(t_box *box)
{
	box->min.x = box->centr.x - box->size;
	box->min.y = box->centr.y - box->size;
	box->min.z = box->centr.z - box->size;
	box->max.x = box->centr.x + box->size;
	box->max.y = box->centr.y + box->size;
	box->max.z = box->centr.z + box->size;
}
void		ft_set_box_to_cam_pos(const t_matrix *camera, void *src)
{
	t_box	*box;

	box = src;
	box->cam_min = mult_vect_matrix_3_3(box->min, camera->invert_matrix);
	box->cam_max = mult_vect_matrix_3_3(box->max, camera->invert_matrix);
	ft_set_box_centr(box);
}

//	sphere intersect function
void		ft_fill_aabb_ray(t_ray *src, t_aabb_ray *dest)
{
	dest->invdir.x = 1 / src->dir.x;
	dest->invdir.y = 1 / src->dir.y;
	dest->invdir.z = 1 / src->dir.z;
	dest->flag[0] = (dest->invdir.x < 0);
	dest->flag[1] = (dest->invdir.y < 0);
	dest->flag[2] = (dest->invdir.z < 0);
}
int8_t		ft_box_intersect(t_ray *ray, const void *data, double_t *t)
{
	t_aabb_ray	r;
	t_v3d		tmin;
	t_v3d		tmax;
	t_v3d		bounds[2];

	ft_fill_aabb_ray(ray, &r);
	bounds[0] = ((t_box*)data)->cam_min;
	bounds[1] = ((t_box*)data)->cam_max;


	tmin.x = (bounds[r.flag[0]].x - ray->orig.x) * r.invdir.x;
	tmax.x = (bounds[1 - r.flag[0]].x - ray->orig.x) * r.invdir.x;

	tmin.y = (bounds[r.flag[1]].y - ray->orig.y) * r.invdir.y;
	tmax.y = (bounds[1 - r.flag[1]].y - ray->orig.y) * r.invdir.y;

	if ((tmin.x > tmax.y) || (tmin.y > tmax.x))
		return (false);

	tmin.x = (tmin.y > tmin.x) ? tmin.y : tmin.x;
	tmax.x = (tmax.y < tmax.x) ? tmax.y : tmax.x;

	tmin.z = (bounds[r.flag[2]].z - ray->orig.z) * r.invdir.z;
	tmax.z = (bounds[1 - r.flag[2]].z - ray->orig.z) * r.invdir.z;

	if ((tmin.x > tmax.z) || (tmin.z > tmax.x))
		return (false);

	tmin.x = (tmin.z > tmin.x) ? tmin.z : tmin.x;
	tmax.x = (tmax.z < tmax.x) ? tmax.z : tmax.x;

	*t = tmin.x;
	if (*t < 0) {
		*t = tmax.x;
		return (false);
	}
	return (true);
}
t_v3d		ft_box_intersect_normals(const t_v3d *hit_point, const t_obj *obj_box)
{
	t_v3d	centr;
	t_v3d	normal;
	t_v3d	v;

	centr = obj_box->get_center(obj_box->data);
	normal = vec_1zero();
	v = vec_3sub(*hit_point, centr);
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
	vec_3normalize(&normal);
	return (normal);
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
t_obj*		ft_new_box(t_v3d *max, t_v3d *min, t_rgb color, double_t size, double_t reflection)
{
	t_obj *obj;
	t_box *new_box;

	if ((ft_mem_box(&obj, &new_box)) == false || !max || size == 0.0)
		return (NULL);
	if (!min)
	{
		new_box->size = size;
		new_box->centr = *max;
		ft_set_box_min_max(new_box);
	}
	else
	{
		new_box->max = *max;
		new_box->min = *min;
		ft_set_box_centr(new_box);
	}

	new_box->color = color;
	new_box->albedo = vec_1double(0.18);
	new_box->reflection = reflection;
	obj->flag = box;
	obj->data = new_box;
	obj->get_albedo = ft_get_box_albedo;
	obj->get_color = ft_get_box_color;
	obj->get_center = ft_get_box_centr;
	obj->intersect = ft_box_intersect;
	obj->get_n_hit = ft_box_intersect_normals;
	obj->get_reflection = ft_get_box_reflection;

	obj->to_camera = ft_set_box_to_cam_pos;
	obj->next = NULL;
	return (obj);
}
