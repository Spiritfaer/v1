#include "vmth.h"

t_matrix*		get_copy_matryx(t_matrix *m)
{
	t_matrix*	copy;
	t_v2i		i = { 0,0 };

	copy = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			copy->matrix[i.y][i.x] = m->matrix[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	copy->invert_matrix = NULL;
	copy->size = m->size;
	return (copy);
}
