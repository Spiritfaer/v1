#include "vmth.h"

t_matrix*		mult_m_to_m(t_matrix *one, t_matrix *two)
{
	//I think it shoud works only cube matrix! Test it!!!
	t_v2i i = { 0,0 };
	t_matrix *mult_m = NULL;
	double buffer_src[32];
	double buffer_dst[32];

	mult_m = get_new_matrix(one->size);
	while (i.y < one->size)
	{
		i.x = 0;
		get_rows(one, i.y, buffer_src);
		while (i.x < one->size)
		{
			get_colums(two, i.x, buffer_dst);
			mult_m->matrix[i.y][i.x] = mult_for_double_buffer(buffer_src, buffer_dst, mult_m->size);
			i.x++;
		}
		i.y++;
	}
	return (mult_m);
}
