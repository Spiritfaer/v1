#include "main.h"

//	geters and setters
t_rgb		ft_get_plane_color(const void* data)
{
	return(((t_plane*)data)->color);
}
t_v3d		get_plane_albedo(const void *data)
{
	return (((t_plane*)data)->albedo);
}
t_v3d		get_center_plane(const void *data)
{
	return(((t_plane*)data)->cam_centr);
}

//	plane and disk intersect function
int8_t		plane_intersect(t_ray *ray, const void *data, double_t *t)
{
	const t_plane	*pl;
	double_t		demon;
	t_v3d			p0l0;

	pl = data;
	demon = vec_3dot(ray->dir, pl->cam_normal);
	if (demon > 1e-6) //or only (demon > 1e-6)
	{
		p0l0 = vec_3sub(pl->cam_centr, ray->orig);
		*t = vec_3dot(p0l0, pl->cam_normal) / demon;
		return (*t >= 0); // and then only (*t >= 0)
	}
	return (false);
}
int8_t		disk_intersect(t_ray *ray, const void *data, double_t *t)
{
	t_v3d		p;
	t_v3d		v;
	double_t	d2;

	*t = 0;
	if (plane_intersect(ray, data, t))
	{
		p = vec_3add(ray->orig, vec_3fmul(ray->dir, *t));
		v = vec_3sub(p, ((t_plane*)data)->cam_centr);
		d2 = vec_3dot(v,v);
		return (d2 <= ((t_plane*)data)->s2);
	}
	return (false);
}
t_v3d		plane_intersect_normals(const t_v3d *hit_point, const t_obj *obj_plane)
{
	//it seems it doesn't work right
	t_plane *pl;

	pl = obj_plane->data;
	return (vec_3invert_dir(&pl->world_normal));
}

//	constructor and destructor
t_obj*	ft_new_plane(t_v3d centr, t_rgb color, double_t radius, int32_t flag)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_plane *new_plane = (t_plane*)malloc(sizeof(t_plane));

	ft_memcpy(&new_plane->world_normal, &centr, sizeof(t_v3d));
	ft_memcpy(&new_plane->color, &color, sizeof(t_rgb));

	if (flag == disk)
	{
		obj->flag = disk;
		obj->intersect = disk_intersect;
	}
	else
	{
		obj->flag = plane;
		obj->intersect = plane_intersect;
	}
	new_plane->albedo = vec_1double(0.18);
	new_plane->size = radius;
	new_plane->s2 = radius * radius;
	new_plane->world_centr = centr;
	new_plane->world_normal = (t_v3d){ 0, -1, 0 };
	new_plane->color = color;
	obj->data = new_plane;
	obj->get_n_hit = plane_intersect_normals;
	obj->get_albedo = get_plane_albedo;
	obj->get_color = ft_get_plane_color;
	obj->get_center = get_center_plane;
	obj->next = NULL;

	return (obj);
}
