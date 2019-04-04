#include "main.h"

t_camera*	make_camera(int32_t size)
{
	t_camera *camera;

	if ((camera = (t_camera*)malloc(sizeof(t_camera))) == NULL)
		return (NULL);
	memset(camera, 0, sizeof(t_camera));
	camera->fov = 60;
	camera->on = 1;
	camera->scale = tan(deg_to_rad(camera->fov * 0.5));
	if (size == 0)
	{
		camera->cam = get_new_matrix(4);
		fill_vertical_matrix(camera->cam);
		camera->cam->matrix[3][0] = 9.084;
		camera->cam->matrix[3][1] = 1.068;
		camera->cam->matrix[3][2] = 14.65;
	}
	else
		fill_random_matrix(camera->cam->matrix, camera->cam->size);
	return (camera);
}

void	destroy_camera(t_camera **camera)
{
	destroy_matrix(&((*camera)->cam));
	free(*camera);
	camera = NULL;
}
