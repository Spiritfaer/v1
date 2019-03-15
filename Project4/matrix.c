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
	while (--n >= 0)
	{
		free(*(data + n));
		*(data + n) = NULL;
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
void			set_buffer(double_t *src, int32_t size, double_t *buffer, double_t mult)
{
	int32_t	i = 0;

	while (i < size)
	{
		buffer[i] = src[i] * mult;
		i++;
	}
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
	//print_matrix(matrix, n);
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
					set_buffer(matrix[i.x], n, buffer, mult);
					minus_matrix_buffer(matrix[i.y], buffer, n);
				}
			}
			i.x++;
			dis *= matrix[i.x - 1][i.x - 1];
		}
	}
	//print_matrix(matrix, n);
	free(matrix);
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
	free(temp);
	//print_matrix(temp, size - 1);
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
					src[i.y][i.x] = -src[i.y][i.x];
			}
			else
			{
				if ((i.x % 2) == 0)
					src[i.y][i.x] = -src[i.y][i.x];
			}
			i.x++;
		}
		i.y++;
	}
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
	print_matrix(minors, size);
	change_symbol(minors, size);
	print_matrix(minors, size);
	return (minors);
}
/*
double_t**		invert_matrix(double_t **matrix, int32_t n)
{
	double_t**	inv_mat;
	double_t**	minor_mat;
	double_t**	tran_mat;
	double_t	dis;

	dis = 0.0;

	return (inv_mat);
}
*/