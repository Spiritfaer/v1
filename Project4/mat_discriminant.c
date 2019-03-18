#include "vmth.h"

static double	get_dis(double a, double b, double c, double d)
{
	return (a * d - c * b);
}

double		get_discriminant(t_matrix *m)
{
	t_matrix	*t_mat;
	double	dis;
	double	buffer[10];
	double	mult;
	t_v2i		i;

	t_mat = get_copy_matryx(m);
	memset(&i, 0, sizeof(t_v2i));
	if (m->size == 2)
		dis = get_dis(m->matrix[0][0], m->matrix[0][1], m->matrix[1][0], m->matrix[1][1]);
	else if (m->size > 2)
	{
		dis = 1;
		while (i.x < m->size && dis != 0)
		{

			i.y = 0 + i.x;
			if (t_mat->matrix[i.y][i.x] == 0)
			{
				swap_for_rows(t_mat, i);
			}
			while (++i.y < m->size)
			{
				if (t_mat->matrix[i.y][i.x] != 0)
				{
					mult = t_mat->matrix[i.y][i.x] / t_mat->matrix[i.x][i.x];
					set_rows_buffer(t_mat->matrix[i.x], t_mat->size, buffer, mult);
					minus_matrix_buffer(t_mat->matrix[i.y], buffer, t_mat->size);
				}
			}
			i.x++;
			if (dis != 0)
				dis *= t_mat->matrix[i.x - 1][i.x - 1];
		}
	}
	destroy_matrix(&t_mat);
	return (dis);
}
