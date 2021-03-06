#include "main.h"


//	geters and setters
t_v3d			ft_get_center_sphere(const void *data)
{
	return(((t_sphere*)data)->cam_centr);
}
t_rgb			ft_get_sphere_color(const void* data)
{
	return(((t_sphere*)data)->color);
}
double_t		ft_get_sphere_reflection(const void *data)
{
	return (((t_sphere*)data)->reflection);
}
void			ft_set_sphere_to_cam_pos(const t_matrix *camera, void *src)
{
	t_sphere	*sph;

	sph = src;
	sph->cam_centr = mult_vect_matrix_3_3(sph->world_centr, camera->invert_matrix);
}

//	sphere intersect function
int8_t			ft_solve_quadratic(t_v3d *abc, t_v2d *tt)
{
	double_t	discr;
	double_t	q;

	discr = abc->y * abc->y - 4 * abc->x * abc->z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		tt->x = tt->y = -0.5 * abc->y / abc->x;
	else
	{
		q = (abc->y > 0) ?
			-0.5 * (abc->y + sqrt(discr)) :
			-0.5 * (abc->y - sqrt(discr));
		tt->x = q / abc->x;
		tt->y = abc->z / q;
	}
	if (tt->x > tt->y)
	{
		//I should use swap... but I forget where it defined
		fs_double_swap(&tt->x, &tt->y);
	}
	return (true);
}
int8_t			ft_sphere_intersect(t_ray *ray, const void *data, double_t *t)
{
	const t_sphere	*s;
	t_v2d			tt = { 0.0, 0.0 };
	t_v3d			light;
	t_v3d			abc;

	// a = D * D where D - ray->dir
	// b = D * 2E where 2E - light
	// c = E * E - 1 where 1 - s->rad 2

	s = data;
	light = vec_3sub(ray->orig, s->world_centr);
	abc.x = vec_3magnitude(ray->dir);				// a
	abc.y = 2 * vec_3dot(ray->dir, light);			// b
	abc.z = vec_3dot(light, light) - s->rad2;		// c 

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
t_v3d			ft_get_sphere_n_hit(const t_v3d *point_hit, const t_obj *obj)
{
	t_v3d		n_hit;

	n_hit = vec_3sub(*point_hit, obj->get_center(obj->data));
	vec_3normalize(&n_hit);
	return (n_hit);
}
//	constructor and destructor
void			ft_del_sphere(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}
t_obj*			ft_new_sphere(t_v3d centr, t_rgb color, double_t radius, double_t reflection)
{
	t_obj		*obj;
	t_sphere	*new_sphere;

	obj = (t_obj*)malloc(sizeof(t_obj));
	new_sphere = (t_sphere*)malloc(sizeof(t_sphere));
	if (!obj || !new_sphere)
		return (NULL);
	ft_memcpy(&new_sphere->world_centr, &centr, sizeof(t_v3d));
	ft_memcpy(&new_sphere->color, &color, sizeof(t_rgb));
	obj->flag = sphere;
	new_sphere->radius = radius;
	new_sphere->rad2 = radius * radius;
	new_sphere->world_centr = centr;
	new_sphere->color = color;
	new_sphere->reflection = reflection;
	obj->data = new_sphere;

	obj->get_center = ft_get_center_sphere;
	obj->get_color = ft_get_sphere_color;
	obj->get_n_hit = ft_get_sphere_n_hit;
	obj->get_reflection = ft_get_sphere_reflection;

	obj->to_camera = ft_set_sphere_to_cam_pos;
	obj->intersect = ft_sphere_intersect;
	obj->next = NULL;
	return (obj);
}
