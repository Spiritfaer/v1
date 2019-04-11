#include "vmth.h"

void			minus_matrix_buffer(double_t *src, double_t *dst, int32_t size)
{
	int32_t		i;
	
	i = 0;
	while (i < size)
	{
		*(src + i) -= *(dst + i);
		i++;
	}
}
