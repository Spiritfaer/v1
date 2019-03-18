#include "vmth.h"

double		get_minor(t_matrix *m, t_v2i i)
{
	t_matrix	*temp = NULL;
	double		result;
	t_v2i		ij = { 0,0 };
	t_v2i		ii = { 0,0 };

	temp = get_new_matrix(m->size - 1);
	while (ij.y < m->size)
	{
		ij.x = 0;
		while (ij.x < m->size)
		{
			if (ij.x != i.x && ij.y != i.y)
			{
				temp->matrix[ii.y][ii.x] = m->matrix[ij.y][ij.x];
				ii.x++;
			}
			ij.x++;
		}
		if (ii.x == temp->size)
		{
			ii.y++;
			ii.x = 0;
		}
		ij.y++;
	}
	result = get_discriminant(temp);
	destroy_matrix(&temp);
	return (result);
}
