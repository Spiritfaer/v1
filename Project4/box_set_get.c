#include "main.h"

t_v3d	get_box_albedo(void *data)
{
	return (((t_box*)data)->albedo);
}

t_v3d	get_box_centr(const void *data)
{
	t_box *b = data;
	return (b->centr);
}

t_rgb	ft_get_box_color(const void* data)
{
	const t_box *temp;
	temp = data;
	return(temp->color);
}

void	set_box_centr(t_box *box)
{
	box->centr.x = (box->min.x + box->max.x) / 2;
	box->centr.y = (box->min.y + box->max.y) / 2;
	box->centr.z = (box->min.z + box->max.z) / 2;
	box->size = vec_3magnitude(vec_3sub(box->max, box->min));
}

void	set_min_max(t_box *box)
{
	box->min.x = box->centr.x - box->size;
	box->min.y = box->centr.y - box->size;
	box->min.z = box->centr.z - box->size;
	box->max.x = box->centr.x + box->size;
	box->max.y = box->centr.y + box->size;
	box->max.z = box->centr.z + box->size;
}
