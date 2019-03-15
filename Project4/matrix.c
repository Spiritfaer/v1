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

void			set_buffer(double_t **src, int32_t size, double_t *buffer, int32_t y, double_t mult)
{
	int32_t	i = 0;

	while (i < size)
	{
		buffer[i] = src[y][i] * mult;
		i++;
	}
}

void		minus_matrix_buffer(double_t *src, double_t *dst, int32_t size)
{
	int32_t i = 0;

	while (i < size)
	{
		*(src + i) -= *(dst + i);
		i++;
	}
}



double_t		get_discriminant(double_t **matrix, int32_t n)
{
	double_t	dis;
	double_t	buffer[10];
	double_t	mult;
	t_v2i		i;
	
	memset(&i, 0, sizeof(t_v2i));
	print_matrix(matrix, n);
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
					set_buffer(matrix, n, buffer, i.x, mult);
					minus_matrix_buffer(matrix[i.y], buffer, n);
				}

			}
			i.x++;
			dis *= matrix[i.x - 1][i.x - 1];
		}
	}
	print_matrix(matrix, n);
	return (dis);
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