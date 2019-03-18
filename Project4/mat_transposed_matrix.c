#include "vmth.h"

t_matrix*		transposed_matrix(t_matrix *m)
{
	t_v2i	i = { 0,0 };
	t_matrix	*temp;

	temp = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			temp->matrix[i.x][i.y] = m->matrix[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	destroy_matrix(&m);
	return (temp);
}
