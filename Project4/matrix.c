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