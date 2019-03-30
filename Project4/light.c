#include "main.h"


t_light*	new_light(t_v3d *pos, t_rgb *color, double_t intensity)
{
	t_light	*l;

	l = NULL;
	if (!pos)
		return (l);

	if (!(l = (t_light*)malloc(sizeof(t_light))))
		return (l);
	l->pos = *pos;
	l->intensity = intensity;
	l->color = *color;
	l->light_color = 1.0;
	l->dir = (t_v3d) { 0, 0, -1 };
	l->invdir = vec_3invert_dir(&l->dir);
	l->albedo = 0,18;
	memset(&l->cam_pos, 0, sizeof(t_v3d));
	l->next = NULL;
	return (l);
}
