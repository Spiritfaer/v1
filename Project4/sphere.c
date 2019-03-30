#include "main.h"

t_v3d	get_center_sphere(const void *data)
{
	const t_sphere *s = data;
	return(s->cam_centr);
}

int8_t	solve_quadratic(const double_t *a, const double_t *b, const double_t *c,
	double_t *x0, double_t *x1)
{
	double_t discr = (*b) * (*b) - 4 * (*a) * (*c);
	double_t q;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		(*x0) = (*x1) = -0.5 * (*b) / (*a);
	else {
		q = ((*b) > 0) ?
			-0.5 * ((*b) + sqrt(discr)) :
			-0.5 * ((*b) - sqrt(discr));
		(*x0) = q / (*a);
		(*x1) = (*c) / q;
	}
	if (x0 > x1)
	{
		//I should use swap... but I forget where it defined
		fs_double_swap(x0, x1);
	}
	return (1);
}



void	ft_del_sphere(t_obj **obj)
{
	free((*obj)->data);
	(*obj)->data = NULL;
	free(*obj);
	(*obj) = NULL;
}

int8_t sphere_intersect(t_v3d *orig, t_v3d *dir, const void *data, double_t *t)
{
	const t_sphere *s = data;
	double_t t0, t1; // solutions for t if the ray intersects 
	t_v3d L = vec_3sub(*orig, s->world_centr);
	double_t a = vec_3magnitude(*dir);
	double_t b = 2 * vec_3dot(*dir, L);
	double_t c = vec_3dot(L, L) - s->rad2;
	if (solve_quadratic(&a, &b, &c, &t0, &t1) == 0)
		return (0);
	if (t0 > t1)
		fs_double_swap(&t0, &t1);
	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0)
			return (0); // both t0 and t1 are negative 
	}
	*t = t0;
	return (1);
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
	new_sphere->rad2 = radius * radius;
	new_sphere->world_centr = centr;
	new_sphere->color = color;

	obj->data = new_sphere;
	obj->get_color = ft_get_sphere_color;
	obj->intersect = sphere_intersect;
	obj->get_center = get_center_sphere;
	obj->next = NULL;

	return (obj);
}
