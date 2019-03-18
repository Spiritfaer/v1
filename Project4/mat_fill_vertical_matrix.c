#include "vmth.h"

void			fill_vertical_matrix(t_matrix *m)
{
	int	i;

	i = 0;
	if (!m || !m->matrix)
		return;
	while (i < m->size)
	{
		m->matrix[i][i] = 1.0;
		i++;
	}
}
