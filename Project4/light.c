#include "main.h"


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
	l->intensity = intensity;
	l->color = *color;
	l->light_color = 1.0;
	//l->dir = (t_v3d) { -20, 15, 15 };
	l->dir = (t_v3d) { 0, 0, 1 };
	l->invdir = vec_3invert_dir(&l->dir);
	memset(&l->cam_pos, 0, sizeof(t_v3d));
	l->next = NULL;
	return (l);
}
