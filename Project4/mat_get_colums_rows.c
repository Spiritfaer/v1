#include "vmth.h"

void			set_rows_buffer(double *src, int size, double *buffer, double mult)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		buffer[i] = src[i] * mult;
		i++;
	}
}

void			get_colums(t_matrix *m, int x, double *buffer)
{
	int	i;
	
	i = 0;
	while (i < m->size)
	{
		buffer[i] = m->matrix[i][x];
		i++;
	}
}
