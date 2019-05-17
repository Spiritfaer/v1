#include "main.h"


/*
t_v3d iCylinder(t_v3d ro, t_v3d rd,
	t_v3d pa, t_v3d pb, double_t ra) // extreme a, extreme b, radius
{
	//vec3 ba = pb - pa;
	t_v3d ba = vec_3sub(pb, pa);

	//vec3  oc = ro - pa;
	t_v3d  oc = vec_3sub(ro, pa);

	double_t baba = vec_3dot(ba, ba);
	double_t bard = vec_3dot(ba, rd);
	double_t baoc = vec_3dot(ba, oc);

	double_t k2 = baba - bard * bard;
	double_t k1 = baba * vec_3dot(oc, rd) - baoc * bard;
	double_t k0 = baba * vec_3dot(oc, oc) - baoc * baoc - ra * ra*baba;

	double_t h = k1 * k1 - k2 * k0;
	if (h < 0.0) 
		return (vec_1double(-1));
		//return vec4(-1.0);
	h = sqrt(h);
	double_t t = (-k1 - h) / k2;

	// body
	double_t y = baoc + t * bard;
	if (y > 0.0 && y < baba) 
		return vec4(t, (oc + t * rd - ba * y / baba) / ra);

	// caps
	t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
	if (abs(k1 + k2 * t) < h)
	{
		return vec4(t, ba*sign(y) / baba);
	}

	return (vec_1double(-1));
}
*/