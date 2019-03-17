#include "main.h"

double_t**		get_new_matrix(uint8_t n)
{
	double_t**	matrix;
	int32_t		i;

	matrix = NULL;
	if ((matrix = (double_t**)malloc(sizeof(double_t*) * n)) == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if ((*(matrix + i) = (double_t*)malloc(sizeof(double_t) * n)) == NULL)
		{
			while(--i >= 0)
			{
				free(*(matrix + i));
			}
			free(matrix);
			matrix = NULL;
			return (NULL);
		}
		memset(*(matrix + i), 0, sizeof(double_t) * n);
		i++;
	}
	return (matrix);
}
double_t**		get_copy_matryx(double_t **src, int32_t size)
{
	double_t**	copy;
	t_v2i		i = { 0,0 };

	copy = get_new_matrix(size);
	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			copy[i.y][i.x] = src[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	return (copy);
}
void			destroy_matrix(double_t **data, int32_t n)
{
	if (!data)
		return ;
	while (--n >= 0)
	{
		if (*(data + n) != NULL)
		{
			free(*(data + n));
			*(data + n) = NULL;
		}
	}
	free(data);
	data = NULL;
}
void			fill_vertical_matrix(double_t **matrix, int32_t n)
{
	int32_t	i;

	i = 0;
	if (!matrix || !n)
		return ;
	while (i < n)
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
void			get_colums(double_t **src, int32_t size, int32_t x, double_t *buffer)
{
	int32_t	i = 0;

	while (i < size)
	{
		buffer[i] = src[i][x];
		i++;
	}
}
void			get_rows(double_t **src, int32_t size, int32_t y, double_t *buffer)
{
	int32_t	i = 0;

	while (i < size)
	{
		buffer[i] = src[y][i];
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
double_t		get_discriminant(double_t **src, int32_t n)
{
	double_t	**matrix;
	double_t	dis;
	double_t	buffer[10];
	double_t	mult;
	t_v2i		i;
	
	matrix = get_copy_matryx(src, n);
	memset(&i, 0, sizeof(t_v2i));
	if (n == 2)
		dis = get_dis(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
	else if (n > 2)
	{
		dis = 1;
		while (i.x < n)
		{
			if (matrix[i.y][i.x] == 0)
				/*сделать свап с другим столбом или строкой*/;
			i.y = 0 + i.x;
			while (++i.y < n)
			{
				if (matrix[i.y][i.x] != 0)
				{
					mult = matrix[i.y][i.x] / matrix[i.x][i.x];
					set_rows_buffer(matrix[i.x], n, buffer, mult);
					minus_matrix_buffer(matrix[i.y], buffer, n);
				}
			}
			i.x++;
			dis *= matrix[i.x - 1][i.x - 1];
		}
	}
	destroy_matrix(matrix, n);
	return (dis);
}
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
void			change_symbol(double_t **src, int32_t size)
{
	t_v2i		i = { 0,0 };

	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			if (i.y == 0 || (i.y % 2) == 0)
			{
				if (i.x % 2)
					src[i.y][i.x] = src[i.y][i.x] * (-1);
			}
			else
			{
				if ((i.x % 2) == 0)
					src[i.y][i.x] = src[i.y][i.x] * (-1);
			}
			i.x++;
		}
		i.y++;
	}
}
double_t**		transposed_matrix(double_t **minors, int32_t size)
{
	t_v2i	i = { 0,0 };
	double_t	**temp;

	temp = get_new_matrix(size);
	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			temp[i.x][i.y] = minors[i.y][i.x];
			i.x++;
		}
		i.y++;
	}
	destroy_matrix(minors, size);
	return (temp);
}
double_t**		get_minors_matrix(double_t **src, int32_t size)
{

	t_v2i	i = { 0,0 };
	double_t **minors = NULL;
	minors = get_new_matrix(size);
	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			minors[i.y][i.x] = get_minor(src, i, size);
			i.x++;

		}
		i.y++;

	}
	change_symbol(minors, size);
	minors = transposed_matrix(minors, size);
	return (minors);
}
double_t**		mult_m_to_m(double_t **one, double_t **two, int32_t size)
{
	t_v2i i = { 0,0 };
	double_t **mult_matrix = NULL;
	double_t buffer_src[10];
	double_t buffer_dst[10];

	mult_matrix = get_new_matrix(size);
	while (i.y < size)
	{
		i.x = 0;
		get_rows(one, size, i.y, buffer_src);
		while (i.x < size)
		{
			get_colums(two, size, i.x, buffer_dst);
			mult_matrix[i.y][i.x] = mult_for_double_buffer(buffer_src, buffer_dst, size);
			i.x++;
		}
		i.y++;
	}
	return (mult_matrix);
}
void			set_inv_matrix(double_t** inv_mat, double_t** minor_mat, double_t dis, int32_t size)
{
	t_v2i	i = { 0,0 };

	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			inv_mat[i.y][i.x] = minor_mat[i.y][i.x] / dis;
			i.x++;
		}
		i.y++;
	}
}
double_t**		invert_matrix(double_t **matrix, int32_t n)
{
	double_t**	inv_mat = NULL;
	double_t**	minor_mat = NULL;
	double_t**	demo_mat = NULL;
	double_t	dis;

	inv_mat = get_new_matrix(n);
	dis = get_discriminant(matrix, n);
	minor_mat = get_minors_matrix(matrix, n);
	set_inv_matrix(inv_mat, minor_mat, dis, n);
	destroy_matrix(minor_mat, n);
	return (inv_mat);
}
