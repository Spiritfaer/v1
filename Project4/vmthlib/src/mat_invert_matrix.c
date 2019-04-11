#include "vmth.h"

static void			set_inv_matrix(t_matrix *m, double_t** minor_mat, double_t dis)
{
	t_v2i	i = { 0,0 };

	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			m->invert_matrix[i.y][i.x] = minor_mat[i.y][i.x] / dis;
			i.x++;
		}
		i.y++;
	}
}

void			invert_matrix(t_matrix *m)
{
	t_matrix*	minor_mat;
	double_t	dis;

	minor_mat = NULL;
	dis = 0;
	if (!m->invert_matrix)
		m->invert_matrix = get_new_m(m->size);
	dis = get_discriminant(m);
	minor_mat = get_minors_matrix(m);
	set_inv_matrix(m, minor_mat->matrix, dis);
	destroy_matrix(&minor_mat);
}
