#include "main.h"

void	ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size)
{
	center->x = 5;
	center->y = -5;
	center->z = -1;

	color->r = 255;
	color->g = 117;
	color->b = 20;
	color->color = (color->r << 16 | color->g << 8 | color->b);

	*radius = 0.9;

	/*
	*centr = { 0,0,50 };	
	*color = { 255,0,0,0 };
	*radius = 25.0;
	*/

}
void	set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->color = (color->r << 16 | color->g << 8 | color->b);
}

void	push_back_obj(t_obj *src, t_obj *des)
{
	t_obj *tmp;

	if (!src || !des)
		return ;
	if (des->next == NULL)
	{
		des->next = src;
		return ;
	}
	tmp = des;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
		{
			tmp->next = src;
			return;
		}
	}
}

void	print_v3d(t_v3d *src, char *str)
{
	printf("%s.x = %10.4f; %s.y = %10.4f; %s.z = %10.4f;\n", str, src->x, str, src->y, str, src->z);
}

void	print_v3i()
{

}

void	color_move(int *color, int up)
{
	if (up)
		(*color)++;
	if ((*color) < 0)
		(*color) = 0;
	if ((*color) > 255)
		(*color) = 0;
}

void	print_sdl(t_sdl *sdl)
{
	printf("\n---Point status---\n");
	printf("init flag = %d", sdl->init_flag);
	printf("window = %p\n", sdl->window);
	printf("renderer = %p\n", sdl->renderer);
	printf("cur_key = %p\n", (void*)sdl->cur_key);
	printf("---Other status---\n");
	printf("srceen_size width = %d, height = %d\n", sdl->screen_size.x, sdl->screen_size.y);
	printf("loop = %d\n", sdl->loop);
	printf("win_name = \"%s\"\n", sdl->win_name);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!n || dst == src)
		return (dst);
	while (n-- && ++i)
		*((unsigned char*)dst)++ = *((unsigned char*)src)++;
	return ((unsigned char*)dst - i);
}

void		fill_2(double_t **matrix, int32_t n)
{
	matrix[0][0] = 2.0;
	matrix[0][1] = 5.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -3.0;
}
void		fill_3(double_t **matrix, int32_t n)
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
void		fill_4(double_t **matrix, int32_t n)
{
	matrix[0][0] = 22.0;
	matrix[0][1] = 5.0;
	matrix[0][2] = 7.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -33.0;
	matrix[1][2] = 4.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 5.0;
	matrix[2][1] = -21.0;
	matrix[2][2] = -3.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 25.0;
	matrix[3][1] = -25.0;
	matrix[3][2] = -5.0;
	matrix[3][3] = 1.0;
}
void		fill_random_matrix(double_t **matrix, int32_t n)
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

//void			minus_matrix_columns(double_t **src, int32_t size, int32_t x, int32_t step)
//{
//	int32_t i = 0;
//	while (i < size)
//	{
//		src[i][x] -= src[i][step];
//		i++;
//	}
//}
//void			minus_matrix_rows(double_t **src, int32_t size, int32_t y, int32_t step)
//{
//	int32_t i = 0;
//	while (i < size)
//	{
//		src[y][i] -= src[step][i];
//		i++;
//	}
//}
//
//void			mult_matrix_columns(double_t **src, double_t mult, int32_t size, int32_t x)
//{
//	int32_t i = 0;
//
//	while (i < size)
//	{
//		src[i][x] *= mult;
//		i++;
//	}
//}
//
//void			mult_matrix_rows(double_t **src, double_t mult, int32_t size, int32_t y)
//{
//	int32_t i = 0;
//
//	while (i < size)
//	{
//		src[y][i] *= mult;
//		i++;
//	}
//}

void			print_matrix(double_t **matrix, int32_t n)
{
	t_v2i i;

	i.x = 0;
	while (i.x < n)
	{
		i.y = 0;
		while (i.y < n)
		{
			printf("%10.6f ", matrix[i.x][i.y]);
			i.y++;
		}
		printf("\n");
		i.x++;
	}
	printf("\n");
}

void		fs_swap(double_t *s, double_t *d)
{
	double_t t;

	t = *s;
	*s = *d;
	*d = t;
}