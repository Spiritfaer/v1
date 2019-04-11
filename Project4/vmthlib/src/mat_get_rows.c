#include "vmth.h"

void			get_rows(t_matrix *m, int32_t y, double_t *buffer)
{
	int32_t		i;
	
	i = 0;
	while (i < m->size)
	{
		buffer[i] = m->matrix[y][i];
		i++;
	}
}
