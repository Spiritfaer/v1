#include "main.h"

t_camera*	make_camera(int32_t size)
{
	t_camera *camera = NULL;

	return (camera);
}

void	destroy_camera(t_camera **camera)
{
	destroy_matrix(&((*camera)->cam));
	free(*camera);
	*camera = NULL;
}
