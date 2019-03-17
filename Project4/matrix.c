#include "main.h"

double_t**		get_new_m(uint8_t n)
{
	double_t	**n_m = NULL;
	int32_t		i = 0;

	if (n > 1)
	{
		if ((n_m = (double_t**)malloc(sizeof(double_t*) * n)) != NULL)
		{
			while (i < n)
			{
				if ((*(n_m + i) = (double_t*)malloc(sizeof(double_t) * n)) == NULL)
				{
					while (--i >= 0)
					{
						free(*(n_m + i));
					}
					free(n_m);
					n_m = NULL;
					return (NULL);
				}
				memset(*(n_m + i), 0, sizeof(double_t) * n);
				i++;
			}
		}
	}
	return (n_m);
}
t_matrix*		get_new_matrix(uint8_t n)
{
	t_matrix*	m_new;

	m_new = NULL;
	if ((m_new = (t_matrix*)malloc(sizeof(t_matrix))) == NULL)
		return (NULL);
	memset(m_new, 0, sizeof(t_matrix));
	if (n > 1)
	{
		m_new->invert_matrix = NULL;
		m_new->size = n;
		m_new->matrix = get_new_m(m_new->size);
	}
	if (m_new->matrix == NULL)
	{
		m_new->size = 0;
		free(m_new);
	}
	return (m_new);
}
/*              ------------- old function -------------
t_matrix*		get_new_matrix(uint8_t n)
{
	t_matrix*	m_new;
	int32_t		i;

	m_new = NULL;
	if ((m_new = (t_matrix*)malloc(sizeof(t_matrix))) == NULL)
		return (NULL);
	memset(m_new, 0, sizeof(t_matrix));

	if ((m_new->matrix = (double_t**)malloc(sizeof(double_t*) * n)) == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if ((*(m_new->matrix + i) = (double_t*)malloc(sizeof(double_t) * n)) == NULL)
		{
			while(--i >= 0)
			{
				free(*(m_new->matrix + i));
			}
			free(m_new->matrix);
			m_new->matrix = NULL;
			return (NULL);
		}
		memset(*(m_new->matrix + i), 0, sizeof(double_t) * n);
		i++;
	}
	m_new->size = n;
	m_new->invert_matrix = NULL;
	return (m_new);
}
*/
t_matrix*		get_copy_matryx(t_matrix *m)
{
	t_matrix*	copy;
	t_v2i		i = { 0,0 };

	copy = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			copy->matrix[i.y][i.x] = m->matrix[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	copy->invert_matrix = NULL;
	copy->size = m->size;
	return (copy);
}
void			free_mat(double_t **data, int32_t size)
{
	if (!data)
		return;
	while (--size >= 0)
	{
		if (*(data + size) != NULL)
		{
			free(*(data + size));
			*(data + size) = NULL;
		}
	}
}
void			destroy_matrix(t_matrix **m)
{
	if (!(*m))
		return ;
	if ((*m)->matrix != NULL)
	{
		free_mat((*m)->matrix, (*m)->size);
		free((*m)->matrix);
		(*m)->matrix = NULL;
	}
	if ((*m)->invert_matrix != NULL)
	{
		free_mat((*m)->invert_matrix, (*m)->size);
		free((*m)->invert_matrix);
		(*m)->invert_matrix = NULL;
	}
	free(*m);
	*m = NULL;
}
void			fill_vertical_matrix(double_t **matrix, int32_t size)
{
	int32_t	i;

	i = 0;
	if (!matrix || !size)
		return ;
	while (i < size)
	{
		matrix[i][i] = 1.0;
		i++;
	}
}
void			set_rows_buffer(double_t *src, int32_t size, double_t *buffer, double_t mult)
{
	int32_t	i = 0;

	while (i < size)
	{
		buffer[i] = src[i] * mult;
		i++;
	}
}
void			get_colums(t_matrix *m, int32_t x, double_t *buffer)
{
	int32_t	i = 0;

	while (i < m->size)
	{
		buffer[i] = m->matrix[i][x];
		i++;
	}
}
void			get_rows(t_matrix *m, int32_t y, double_t *buffer)
{
	int32_t	i = 0;

	while (i < m->size)
	{
		buffer[i] = m->matrix[y][i];
		i++;
	}
}
double_t		mult_for_double_buffer(double_t *src, double_t *dst, int32_t size)
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
void			minus_matrix_buffer(double_t *src, double_t *dst, int32_t size)
{
	int32_t i = 0;

	while (i < size)
	{
		*(src + i) -= *(dst + i);
		i++;
	}
}
double_t		get_discriminant(t_matrix *m)
{
	t_matrix	*t_mat;
	double_t	dis;
	double_t	buffer[10];
	double_t	mult;
	t_v2i		i;
	
	t_mat = get_copy_matryx(m);
	memset(&i, 0, sizeof(t_v2i));
	if (m->size == 2)
		dis = get_dis(m->matrix[0][0], m->matrix[0][1], m->matrix[1][0], m->matrix[1][1]);
	else if (m->size > 2)
	{
		dis = 1;
		while (i.x < m->size)
		{
			if (t_mat->matrix[i.y][i.x] == 0)
				/*сделать свап с другим столбом или строкой*/;
			i.y = 0 + i.x;
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
			dis *= t_mat->matrix[i.x - 1][i.x - 1];
		}
	}
	destroy_matrix(&t_mat);
	return (dis);
}
/*              ------------- old function -------------
double_t		get_minor(double_t **src, t_v2i i, int32_t size)
{
	double_t	**temp = NULL;
	double_t	result;
	t_v2i		j = { 0,0 };
	t_v2i		m = { 0,0 };

	temp = get_new_matrix(size - 1);
	while (j.y < size)
	{
		j.x = 0;
		while (j.x < size)
		{
			if (j.x != i.x && j.y != i.y)
			{
				temp[m.y][m.x] = src[j.y][j.x];
				m.x++;
			}
			j.x++;
		}
		if (m.x == size - 1)
		{
			m.y++;
			m.x = 0;
		}
		j.y++;
	}
	result = get_discriminant(temp, size - 1);
	destroy_matrix(temp, size - 1);
	return (result);
}
*/
double_t		get_minor(t_matrix *m, t_v2i i)
{
	t_matrix	*temp = NULL;
	double_t	result;
	t_v2i		ij = { 0,0 };
	t_v2i		ii = { 0,0 };

	temp = get_new_matrix(m->size - 1);
	while (ij.y < m->size)
	{
		ij.x = 0;
		while (ij.x < m->size)
		{
			if (ij.x != i.x && ij.y != i.y)
			{
				temp->matrix[ii.y][ii.x] = m->matrix[ij.y][ij.x];
				ii.x++;
			}
			ij.x++;
		}
		if (ii.x == temp->size)
		{
			ii.y++;
			ii.x = 0;
		}
		ij.y++;
	}
	result = get_discriminant(temp);
	destroy_matrix(&temp);
	return (result);
}
void			change_symbol(t_matrix *m)
{
	t_v2i		i = { 0,0 };

	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			if (i.y == 0 || (i.y % 2) == 0)
			{
				if (i.x % 2)
					m->matrix[i.y][i.x] *= (-1);
			}
			else
			{
				if ((i.x % 2) == 0)
					m->matrix[i.y][i.x] *= (-1);
			}
			i.x++;
		}
		i.y++;
	}
}
t_matrix*		transposed_matrix(t_matrix *m)
{
	t_v2i	i = { 0,0 };
	t_matrix	*temp;

	temp = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			temp->matrix[i.x][i.y] = m->matrix[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	destroy_matrix(&m);
	return (temp);
}
t_matrix*		get_minors_matrix(t_matrix *m)
{
	t_v2i	i = { 0,0 };
	t_matrix *minors = NULL;
	minors = get_new_matrix(m->size);
	while (i.y < m->size)
	{
		i.x = 0;
		while (i.x < m->size)
		{
			minors->matrix[i.y][i.x] = get_minor(m, i);
			i.x++;
		}
		i.y++;
	}
	change_symbol(minors);
	minors = transposed_matrix(minors);
	return (minors);
}
t_matrix*		mult_m_to_m(t_matrix *one, t_matrix *two)
{
	//I think it shoud works only cube matrix! Test it!!!
	t_v2i i = { 0,0 };
	t_matrix *mult_m = NULL;
	double_t buffer_src[32];
	double_t buffer_dst[32];

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
void			set_inv_matrix(t_matrix *m, double_t** minor_mat, double_t dis)
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
