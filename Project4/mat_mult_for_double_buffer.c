#include "vmth.h"

double		mult_for_double_buffer(double *src, double *dst, int size)
{
	double	sum = 0;
	int		i = 0;

	if (!src || !dst)
		return (sum);
	while (i < size)
	{
		sum += src[i] * dst[i];
		i++;
	}
	return (sum);
}
