#include "main.h"

SDL_Surface *new_canvas(uint32_t width, uint32_t height)
{
	SDL_Surface *new_surf;
	new_surf = SDL_CreateRGBSurface(0, width, height, 32,
		0, 0, 0, 0);
	return (new_surf);
}


void	ft_del_sdl(t_sdl *sdl)
{
	if (sdl->renderer)
	{
		SDL_DestroyRenderer(sdl->renderer);
	}

	if (sdl->window)
		SDL_DestroyWindow(sdl->window);
	if (sdl->init_flag)
		SDL_Quit();
}

int8_t	ft_init_sdl(t_sdl *sdl)
{
	int8_t	result;

	result = 1;
	if ((sdl->init_flag = SDL_Init(SDL_INIT_EVERYTHING)) < 0)
	{
		result--;
		printf("ERROR! SDL_INIT\n");
	}
	else
	{
		sdl->window = SDL_CreateWindow(sdl->win_name, 10, 40,
			sdl->screen_size.x, sdl->screen_size.y, SDL_WINDOW_SHOWN);
		if (!sdl->window)
		{
			result--;
			printf("ERROR! CREATED WINDOWS FAIL\n");
		}
		else
		{
			sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}
	}
	return (result);
}

t_sdl	*ft_new_sdl(void)
{
	t_sdl* sdl;

	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	memset(sdl, 0, sizeof(t_sdl));
	if (!sdl)
	{
		printf("ERROR! MAKE NEW SDL STRUCT!\n");
		return (NULL);
	}
	else
	{
		sdl->init_flag = 0;
		sdl->window = NULL;
		sdl->renderer = NULL;
		sdl->cur_key = NULL;
		sdl->win_name = "RT_V1";
		sdl->screen_size.x = WIN_SIZE_W;
		sdl->screen_size.y = WIN_SIZE_H;
		sdl->iar = ((double_t)sdl->screen_size.x) / ((double_t)sdl->screen_size.y);
		sdl->canvas = new_canvas(sdl->screen_size.x, sdl->screen_size.y);
		sdl->loop = 1;
		if (ft_init_sdl(sdl) < 0)
		{
			free(sdl);
			sdl = NULL;
			return (NULL);
		}
	}
	return (sdl);
}