#include "main.h"

//	geters and setters
t_v3d			ft_get_center_cone(const void *data)
{
	return(((t_cone*)data)->cam_centr);
}
t_v3d			ft_get_cone_albedo(const void *data)
{
	return (((t_cone*)data)->albedo);
}
t_rgb			ft_get_cone_color(const void* data)
{
	return(((t_cone*)data)->color);
}
void			ft_set_cone_to_cam_pos(const t_matrix *camera, void *src)
{
	t_cone	*cone;

	cone = src;
	cone->cam_centr = mult_vect_matrix_3_3(cone->world_centr, camera->invert_matrix);
}

//	cone intersect function

int8_t			ft_cone_intersect(t_ray *ray, const void *data, double_t *t)
{
	// a = D * D		where D - ray->dir 
	// b = D * 2E		where 2E - light
	// c = E * E - 1	where 1 - s->rad 2

	// a = xD2 + yD2 - zD2
	// b = 2xExD + 2yEyD - 2zEzD
	// c = xE2 + yE2 - zE2

	const t_cone	*cone;
	t_v2d			tt = { 0.0, 0.0 };
	t_v3d			light;
	t_v3d			abc;

	
	cone = data;
	light = vec_3sub(ray->orig, cone->world_centr);
	vec_3normalize(&light);

	t_v3d dist = vec_3sub(ray->orig, cone->cam_centr);
	vec_3normalize(&cone->cam_normal);


	abc.x = vec_3dot(ray->dir, ray->dir) - (1 + pow(tan(cone->size), 2)) * pow(vec_3dot(ray->dir, cone->cam_normal), 2);
	abc.y = 2 * (vec_3dot(ray->dir, light) - (1 + pow(tan(cone->size), 2)) * vec_3dot(ray->dir, cone->cam_normal) * vec_3dot(light, cone->cam_normal));
	abc.z = vec_3dot(light, light) - (1 + pow(tan(cone->size), 2)) * pow(vec_3dot(light, cone->cam_normal), 2);
	/*
	abc.x = vec_3dot(ray->dir, ray->dir) - (1 + pow(tan(cone->size), 2)) * pow(vec_3dot(ray->dir, cone->cam_normal), 2);
	abc.y = 2 * (vec_3dot(ray->dir, dist) - (1 + pow(tan(cone->size), 2)) * vec_3dot(ray->dir, cone->cam_normal) * vec_3dot(dist, cone->cam_normal));
	abc.z = vec_3dot(dist, dist) - (1 + pow(tan(cone->size), 2)) * pow(vec_3dot(dist, cone->cam_normal), 2);

	abc.x = (ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y) - (ray->dir.z * ray->dir.z);		// a
	abc.y = (2 * ray->dir.x * light.x) + (2 * ray->dir.y * light.y) - (2 * ray->dir.z * light.z);	// b
	abc.z = (light.x * light.x) + (light.y * light.y) - (light.z * light.z);						// c
	*/
	if (ft_solve_quadratic(&abc, &tt) == false)
		return (false);
	if (tt.x > tt.y)
		fs_double_swap(&tt.x, &tt.y);
	if (tt.x < 0)
	{
		tt.x = tt.y; // if tt.x is negative, let's use t1 instead 
		if (tt.x < 0)
			return (false); // both tt.x and t1 are negative 
	}
	*t = tt.x;
	return (true);
}
t_v3d			ft_get_cone_n_hit(const t_v3d *point_hit, const t_obj *obj)
{
	t_v3d		n_hit;

	n_hit = vec_3sub(*point_hit, obj->get_center(obj->data));
	vec_3normalize(&n_hit);
	return (n_hit);
}

t_obj*			ft_new_cone(t_v3d centr, t_rgb color, double_t radius)
{
	t_obj		*obj;
	t_cone		*new_cone;

	obj = (t_obj*)malloc(sizeof(t_obj));
	new_cone = (t_cone*)malloc(sizeof(t_sphere));
	if (!obj || !new_cone)
		return (NULL);
	ft_memcpy(&new_cone->world_centr, &centr, sizeof(t_v3d));
	ft_memcpy(&new_cone->color, &color, sizeof(t_rgb));
	obj->flag = cone;


	new_cone->albedo = vec_1double(0.18);
	new_cone->radius = radius;
	//new_cone->rad2 = radius * radius;
	new_cone->world_centr = centr;
	new_cone->world_normal = (t_v3d) { 0, 0, -1 };
	new_cone->size = 0.5;
	new_cone->color = color;


	obj->data = new_cone;
	obj->get_center = ft_get_center_cone;
	obj->get_albedo = ft_get_cone_albedo;
	obj->get_color = ft_get_cone_color;
	obj->get_n_hit = ft_get_cone_n_hit;

	obj->to_camera = ft_set_cone_to_cam_pos;
	obj->intersect = ft_cone_intersect;
	obj->next = NULL;
	return (obj);
}

