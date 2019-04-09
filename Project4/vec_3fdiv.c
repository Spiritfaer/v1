#include "vmth.h"

t_v3d	vec_3fdiv(t_v3d v, double_t f)
{
	t_v3d	res;

	res.x = v.x / f;
	res.y = v.y / f;
	res.z = v.z / f;
	return (res);
}
