#include "vmth.h"

t_matrix*		get_minors_matrix(t_matrix *m)
{
	t_v2i	i = { 0,0 };
	t_matrix *minors = NULL;
	minors = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			minors->matrix[i.y][i.x] = get_minor(m, i);
			i.x++;
		}
		i.y++;
	}
	change_symbol(minors);
	minors = transposed_matrix(minors);
	return (minors);
}
