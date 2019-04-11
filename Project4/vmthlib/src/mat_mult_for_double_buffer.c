#include "vmth.h"

double		mult_for_double_buffer(double_t *src, double_t *dst, int32_t size)
{
	double_t	sum = 0;
	int32_t		i = 0;

	if (!src || !dst)
		return (sum);
	while (i < size)
	{
		sum += src[i] * dst[i];
		i++;
	}
	return (sum);
}
