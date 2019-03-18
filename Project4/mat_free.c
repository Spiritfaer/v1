#include "vmth.h"

void			free_mat(double **data, int size)
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
		return;
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
