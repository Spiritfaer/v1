#include "vmth.h"

void			set_rows_buffer(double_t *src, int32_t size, double_t *buffer, double_t mult)
{
	int32_t	i;
	
	i = 0;
	while (i < size)
	{
		buffer[i] = src[i] * mult;
		i++;
	}
}

void			get_colums(t_matrix *m, int32_t x, double_t *buffer)
{
	int32_t	i;
	
	i = 0;
	while (i < m->size)
	{
		buffer[i] = m->matrix[i][x];
		i++;
	}
}
