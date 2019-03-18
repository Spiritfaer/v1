#include "vmth.h"

void			get_rows(t_matrix *m, int y, double *buffer)
{
	int	i;
	
	i = 0;
	while (i < m->size)
	{
		buffer[i] = m->matrix[y][i];
		i++;
	}
}
