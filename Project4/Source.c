#include "main.h"

SDL_Surface *new_canvas(uint32_t width, uint32_t height)
{
	SDL_Surface *new_surf;
	new_surf = SDL_CreateRGBSurface(0, width, height, 32,
		0, 0, 0, 0);
	return (new_surf);
}

void	ft_draw(const t_sdl *sdl, SDL_Surface *canvas, const t_obj *obj)
{
	int x;
	int y;
	uint32_t *tmp = (uint32_t*)canvas->pixels;

	x = 0;

	while (x < sdl->screen_size.x)
	{
		y = 0;
		while (y < sdl->screen_size.y)
		{
			if (obj->intersect(x, y, (t_sphere*)obj->data))
				tmp[x + y * sdl->screen_size.x] = ((t_sphere*)obj->data)->color.color;
				//((uint32_t*)canvas->pixels)[x + y * sdl->screen_size.x] = 0xFFFFFF;

			y++;
		}
		x++;
	}
}

void	ft_render(t_sdl *sdl, t_obj *obj)
{
	SDL_Surface *canvas = NULL;
	SDL_Texture *screen = NULL;
	canvas = new_canvas(sdl->screen_size.x, sdl->screen_size.y);

	

	//sdl->renderer;
	while (sdl->loop)
	{
		//memset(canvas->pixels, 0, sdl->screen_size.x * sdl->screen_size.y);
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		if (sdl->event.type == SDL_QUIT)
			sdl->loop = 0;
		if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
			sdl->loop = 0;

		ft_draw(sdl, canvas, obj);
		screen = SDL_CreateTextureFromSurface(sdl->renderer, canvas);

		SDL_RenderCopy(sdl->renderer, screen, 0, 0);
		SDL_RenderPresent(sdl->renderer);

		SDL_RenderClear(sdl->renderer);
		SDL_DestroyTexture(screen);
	}
	SDL_FreeSurface(canvas);
}

int main(int argc, char ** argv)
{
	t_sdl		*sdl = NULL;
	t_obj		*obj = NULL;
	t_v3d		centr;
	t_rgb		color;
	double_t	radius;


	sdl = ft_new_sdl();
	
	ft_temp_fill(&centr, &color, &radius, sdl->screen_size);
	obj = ft_new_sphere(centr, color, radius);
	obj_info(obj);

	int32_t matrix_size = 14;
	double_t **test_matrix = get_new_matrix(matrix_size);

	print_matrix(test_matrix, matrix_size);
	fill_vertical_matrix(test_matrix, matrix_size);
	print_matrix(test_matrix, matrix_size);
	destroy_matrix(test_matrix, matrix_size);

	ft_render(sdl, obj);

	if (obj)
		ft_del_sphere(&obj);

	if (sdl)
	{
		ft_del_sdl(sdl);
		free(sdl);
	}

	printf("ok!\n");
	return (0);
}
