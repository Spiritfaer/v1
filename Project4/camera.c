#include "main.h"

t_camera*	new_camera(t_v3d *pos, t_rgb *color, double_t fov)
{
	t_camera *camera;

	if ((camera = (t_camera*)malloc(sizeof(t_camera))) == NULL)
		return (NULL);
	memset(camera, 0, sizeof(t_camera));
	camera->fov = fov;
	camera->on = 1;
	camera->scale = tan(deg_to_rad(camera->fov * 0.5));
	camera->cam = get_new_matrix(4);
	fill_vertical_matrix(camera->cam);
	camera->cam->matrix[3][0] = pos->x;
	camera->cam->matrix[3][1] = pos->y;
	camera->cam->matrix[3][2] = pos->z;
	camera->cam->invert_matrix = NULL;
	camera->bg_color = *color;
	return (camera);
}

void	destroy_camera(t_camera **camera)
{
	destroy_matrix(&((*camera)->cam));
	free(*camera);
	*camera = NULL;
}
