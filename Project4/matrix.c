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

void	fill_vertical_matrix(double_t **matrix, int32_t n)
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

void	print_matrix(double_t **matrix, int32_t n)
{
	t_v2i i;

	i.x = 0;
	while (i.x < n)
	{
		i.y = 0;
		while (i.y < n)
		{
			printf("%6.2f ", matrix[i.x][i.y]);
			i.y++;
		}
		printf("\n");
		i.x++;
	}
	printf("\n");
}

void	fill_2(double_t **matrix, int32_t n)
{
	matrix[0][0] = 2.0;
	matrix[0][1] = 5.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -3.0;
}
void	fill_3(double_t **matrix, int32_t n)
{
	matrix[0][0] = 22.0;
	matrix[0][1] = 5.0;
	matrix[0][2] = 7.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -33.0;
	matrix[1][2] = 4.0;
	matrix[2][0] = 5.0;
	matrix[2][1] = -21.0;
	matrix[2][2] = -3.0;
}
void	fill_4(double_t **matrix, int32_t n)
{
	printf("ERROR! you foget about fill_4 function!\n");
}

void	fill_random_matrix(double_t **matrix, int32_t n)
{

	if (!matrix || !n)
		return;
	if (n == 2)
		fill_2(matrix, n);
	else if (n == 3)
		fill_3(matrix, n);
	else if (n == 4)
		fill_4(matrix, n);
	else
		printf("ERROR! fill_random_matrix have wrong matrix size!\n");
}

double_t	get_dis(double_t a, double_t b, double_t c, double_t d)
{
	return (a * d - c * b);
}

double_t		get_discriminant(double_t **matrix, int32_t n)
{
	double_t	dis;

	if (n == 2)
		dis = get_dis(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
	else if (n == 3)
	{
		dis = get_dis(matrix[1][1], matrix[1][2], matrix[2][1], matrix[2][2]) * matrix[0][0];
		dis -= get_dis(matrix[1][0], matrix[1][2], matrix[2][0], matrix[2][2]) * matrix[0][1];
		dis += get_dis(matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]) * matrix[0][2];
	}
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