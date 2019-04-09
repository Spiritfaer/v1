#include "main.h"


t_v3d		get_light_dir(t_hit *hit, t_light *light)
{
	t_v3d	dir;
	t_v3d	color;

	dir = vec_3sub(light->cam_pos, hit->point_hit);
	light->r2 = vec_3magnitude(dir);
	vec_3normalize(&dir);

	color.x = light->color.r;
	color.y = light->color.g;
	color.z = light->color.b;


	light->intensity_light = vec_3fdiv(color, (4 * M_PI * light->r2));
	return (dir);
}

t_light*	new_light(t_v3d *pos, t_rgb *color, double_t intensity)
{
	t_light	*l;

	l = NULL;
	if (!pos)
		return (l);

	if (!(l = (t_light*)malloc(sizeof(t_light))))
		return (l);
	l->transform = get_new_matrix(4);
	fill_vertical_matrix(l->transform);
	l->transform->matrix;
	l->pos = *pos;
	l->power_light = intensity;
	l->color = *color;
	l->light_color = 1.0;
	//l->dir = (t_v3d) { -20, 15, 15 };
	l->dir = (t_v3d) { 0, 0, 1 };
	l->invdir = vec_3invert_dir(&l->dir);
	memset(&l->cam_pos, 0, sizeof(t_v3d));
	l->next = NULL;
	return (l);
}
