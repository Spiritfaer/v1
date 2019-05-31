#include "main.h"

//	geters and setters
t_rgb		ft_get_plane_color(const void* data)
{
	return(((t_plane*)data)->color);
}
t_v3d		ft_get_center_plane(const void *data)
{
	return(((t_plane*)data)->cam_centr);
}
double_t	ft_get_plane_reflection(const void *data)
{
	return (((t_plane*)data)->reflection);
}

void		ft_set_plane_to_cam_pos(const t_matrix *camera, void *src)
{
	t_plane *pl;

	pl = src;
	pl->cam_centr = mult_vect_matrix_3_3(pl->world_centr, camera->invert_matrix);
	pl->cam_normal = mult_vect_matrix_3_3(pl->world_normal, camera->invert_matrix);
	vec_3normalize(&pl->cam_normal);
}

//	plane and disk intersect function
int8_t		ft_plane_intersect(t_ray *ray, const void *data, double_t *t)
{
	const t_plane	*pl;
	double_t		demon;
	t_v3d			p0l0;

	pl = data;
	demon = vec_3dot(ray->dir, pl->cam_normal);
	if (demon > 1e-6 || demon < 1e-6) //or only (demon > 1e-6)
	{
		p0l0 = vec_3sub(pl->cam_centr, ray->orig);
		*t = vec_3dot(p0l0, pl->cam_normal) / demon;
		return (*t >= 0); // and then only (*t >= 0)
	}
	return (false);
}
int8_t		ft_disk_intersect(t_ray *ray, const void *data, double_t *t)
{
	t_v3d		p;
	t_v3d		v;
	double_t	d2;

	*t = 0;
	if (ft_plane_intersect(ray, data, t))
	{
		p = vec_3add(ray->orig, vec_3fmul(ray->dir, *t));
		v = vec_3sub(p, ((t_plane*)data)->cam_centr);
		d2 = vec_3dot(v,v);
		return (d2 <= ((t_plane*)data)->s2);
	}
	return (false);
}
t_v3d		ft_plane_intersect_normals(const t_v3d *hit_point, const t_obj *obj_plane)
{
	//it seems it doesn't work right
	t_plane *pl;

	pl = obj_plane->data;
	return (vec_3invert_dir(&pl->world_normal));
}

//	constructor and destructor
t_obj*	ft_new_plane(t_v3d centr, t_rgb color, double_t radius, int32_t flag, double_t reflection)
{
	t_obj *obj = (t_obj*)malloc(sizeof(t_obj));
	t_plane *new_plane = (t_plane*)malloc(sizeof(t_plane));

	//ft_memcpy(&new_plane->world_normal, &centr, sizeof(t_v3d));
	//ft_memcpy(&new_plane->color, &color, sizeof(t_rgb));

	if (flag == disk)
	{
		obj->flag = disk;
		obj->intersect = ft_disk_intersect;
	}
	else
	{
		obj->flag = plane;
		obj->intersect = ft_plane_intersect;
	}
	new_plane->size = radius;
	new_plane->s2 = radius * radius;
	new_plane->world_centr = centr;
	new_plane->world_normal = (t_v3d){ 0, -1, 0 };
	new_plane->color = color;
	new_plane->reflection = reflection;
	obj->data = new_plane;
	obj->get_n_hit = ft_plane_intersect_normals;
	obj->get_color = ft_get_plane_color;
	obj->get_center = ft_get_center_plane;
	obj->get_reflection = ft_get_plane_reflection;

	obj->to_camera = ft_set_plane_to_cam_pos;
	obj->next = NULL;

	return (obj);
}
