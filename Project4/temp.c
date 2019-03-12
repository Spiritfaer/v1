#include "main.h"

void	ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size)
{
	center->x = 2;
	center->y = -1;
	center->z = -5;

	color->r = 255;
	color->g = 117;
	color->b = 20;
	color->color = (color->r << 16 | color->g << 8 | color->b);

	*radius = 50.0;

	/*
	*centr = { 0,0,50 };	
	*color = { 255,0,0,0 };
	*radius = 25.0;
	*/
	t_v2d center_proj;
	t_v2d center_remap;
	t_v2d center_pixel;


	center_proj.x = center->x / -center->z;
	center_proj.y = center->y / -center->z;

	center_remap.x = (1 + center_proj.x) / 2;
	center_remap.y = (1 + center_proj.y) / 2;

	center_pixel.x = center_remap.x * win_size.x;
	center_pixel.y = center_remap.y * win_size.y;

	center->x = center_pixel.x;
	center->y = center_pixel.y;
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
