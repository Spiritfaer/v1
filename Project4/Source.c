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
	t_v2i i = { 0, 0 };
	uint32_t *tmp = (uint32_t*)canvas->pixels;

	while (i.x < sdl->screen_size.x)
	{
		i.y = 0;
		while (i.y < sdl->screen_size.y)
		{
			if (obj->intersect(i, (t_sphere*)obj->data))
				tmp[i.x + i.y * sdl->screen_size.x] = ((t_sphere*)obj->data)->color.color;
				//((uint32_t*)canvas->pixels)[x + y * sdl->screen_size.x] = 0xFFFFFF;

			i.y++;
		}
		i.x++;
	}
}

t_matrix*	make_camera(int32_t size)
{
	t_matrix *camera;

	camera = NULL;
	if (size == 0)
	{
		camera = get_new_matrix(4);
		fill_vertical_matrix(camera);
		camera->matrix[3][2] = 50;
	}
	else
		fill_random_matrix(camera->matrix, camera->size);
	
	return (camera);
}

t_v3d	mult_vect_matrix(t_v3d world_centr, double_t **invert_matrix)
{
	double_t a, b, c, w;
	t_v3d point = { 0, 0, 0 };

	a = world_centr.x * invert_matrix[0][0] + world_centr.y * invert_matrix[0][1] + world_centr.z * invert_matrix[0][2] + invert_matrix[0][3];
	b = world_centr.x * invert_matrix[1][0] + world_centr.y * invert_matrix[1][1] + world_centr.z * invert_matrix[1][2] + invert_matrix[1][3];
	c = world_centr.x * invert_matrix[2][0] + world_centr.y * invert_matrix[2][1] + world_centr.z * invert_matrix[2][2] + invert_matrix[2][3];
	w = world_centr.x * invert_matrix[3][0] + world_centr.y * invert_matrix[3][1] + world_centr.z * invert_matrix[3][2] + invert_matrix[3][3];


	point.x = a / w;
	point.y = b / w;
	point.z = c / w;

	return (point);
}

void	refresh_obj(const t_matrix *camera, t_obj *obj)
{
	t_v3d	point;
	if (obj->flag == sphere)
	{
		point = mult_vect_matrix(((t_sphere*)obj->data)->world_centr, camera->invert_matrix);
		((t_sphere*)obj->data)->cam_centr = point;
		printf("\n%f, %f, %f\n", point.x, point.y, point.z);
	}
}

void	time_tick(t_time *t)
{
	t->old_time = t->time;
	t->time = SDL_GetTicks();
	t->frame_time = (t->time - t->old_time) / 1000.0;
	t->speed = t->frame_time * 30.0;
}

void		move_camera(uint8_t *cur_key, t_matrix *camera, t_time *time)
{
	if (cur_key[SDL_SCANCODE_W])
	{
		camera->matrix[3][1] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_S])
	{
		camera->matrix[3][1] -= time->speed;
	}
	if (cur_key[SDL_SCANCODE_A])
	{
		camera->matrix[3][0] -= time->speed;
	}
	if (cur_key[SDL_SCANCODE_D])
	{
		camera->matrix[3][0] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_SPACE])
	{
		camera->matrix[3][2] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_LCTRL])
	{
		camera->matrix[3][2] -= time->speed;
	}
}

void		ft_render(t_sdl *sdl, t_obj *obj)
{
	SDL_Surface *canvas = NULL;
	SDL_Texture *screen = NULL;
	t_time		time;
	memset(&time, 0, sizeof(t_time));
	canvas = new_canvas(sdl->screen_size.x, sdl->screen_size.y);

	t_matrix*	camera = NULL;

	camera = make_camera(0);
	//print_matrix(camera->matrix, camera->size);
	//print_matrix(camera->invert_matrix, camera->size);
	//sdl->renderer;
	while (sdl->loop)
	{
		invert_matrix(camera);
		refresh_obj(camera, obj);

		//memset(canvas->pixels, 0, sdl->screen_size.x * sdl->screen_size.y);
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		if (sdl->event.type == SDL_QUIT)
			sdl->loop = 0;
		if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
			sdl->loop = 0;
		time_tick(&time);
		move_camera(sdl->cur_key, camera, &time);

		ft_draw(sdl, canvas, obj);
		screen = SDL_CreateTextureFromSurface(sdl->renderer, canvas);

		SDL_RenderCopy(sdl->renderer, screen, 0, 0);
		SDL_RenderPresent(sdl->renderer);

		SDL_RenderClear(sdl->renderer);
		SDL_DestroyTexture(screen);
	}
	destroy_matrix(&camera);
	SDL_FreeSurface(canvas);
}

int main(int argc, char ** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtDumpMemoryLeaks();




	t_sdl		*sdl = NULL;
	t_obj		*obj = NULL;
	t_v3d		centr;
	t_rgb		color;
	double_t	radius;


	sdl = ft_new_sdl();
	
	ft_temp_fill(&centr, &color, &radius, sdl->screen_size);
	obj = ft_new_sphere(centr, color, radius);
	obj_info(obj);

	_CrtMemState tmp;
	_CrtMemCheckpoint(&tmp);

	ft_render(sdl, obj);

	if (obj)
		ft_del_sphere(&obj);

	if (sdl)
	{
		ft_del_sdl(sdl);
		free(sdl);
	}
	_CrtMemDumpAllObjectsSince(&tmp);
	printf("ok!\n");
	return (0);
}
