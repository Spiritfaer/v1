#include "vmth.h"

void			minus_matrix_buffer(double *src, double *dst, int size)
{
	int i;
	
	i = 0;
	while (i < size)
	{
		*(src + i) -= *(dst + i);
		i++;
	}
}
