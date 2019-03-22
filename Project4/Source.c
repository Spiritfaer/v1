#include "main.h"

SDL_Surface *new_canvas(uint32_t width, uint32_t height)
{
	SDL_Surface *new_surf;
	new_surf = SDL_CreateRGBSurface(0, width, height, 32,
		0, 0, 0, 0);
	return (new_surf);
}
void	ft_draw(const t_sdl *sdl, SDL_Surface *canvas, const t_obj *obj, t_camera *camera)
{
	t_v3i		orig	= { 0, 0, 0 };
	t_v3d		dir = /*camera->matrix*/ { 0, 0, -1 };
	double_t	t		= DBL_MAX;
	uint32_t	*tmp	= (uint32_t*)canvas->pixels;

	while (orig.x < sdl->screen_size.x)
	{
		orig.y = 0;
		while (orig.y < sdl->screen_size.y)
		{
			if (obj->intersect(&orig, &dir, (t_sphere*)obj->data, &t) && t > 0)
			{
				tmp[orig.x + orig.y * sdl->screen_size.x] = ((t_sphere*)obj->data)->color.color;
			}
				//((uint32_t*)canvas->pixels)[x + y * sdl->screen_size.x] = 0xFFFFFF;
			//Vec3f hitPoint = orig + dir * t;
			orig.y++;
		}
		orig.x++;
	}
}

t_camera*	make_camera(int32_t size)
{
	t_camera *camera;

	if ((camera = (t_camera*)malloc(sizeof(t_camera))) == NULL)
		return (NULL);
	memset(camera, 0, sizeof(t_camera));

	if (size == 0)
	{
		camera->cam = get_new_matrix(4);
		fill_vertical_matrix(camera->cam);
		camera->cam->matrix[3][2] = 50;
		camera->cam->matrix[3][0] = 25;
	}
	else
		fill_random_matrix(camera->cam->matrix, camera->cam->size);
	
	return (camera);
}

void	destroy_camera(t_camera **camera)
{
	destroy_matrix(&((*camera)->cam));
	free(*camera);
	camera = NULL;
}

t_v3d	mult_vect_matrix(t_v3d world_centr, double_t **invert_matrix)
{
	double_t w;
	t_v3d point = { 0, 0, 0 };

	point.x = world_centr.x * invert_matrix[0][0] + world_centr.y * invert_matrix[1][0] + world_centr.z * invert_matrix[2][0] + invert_matrix[3][0];
	point.y = world_centr.x * invert_matrix[0][1] + world_centr.y * invert_matrix[1][1] + world_centr.z * invert_matrix[2][1] + invert_matrix[3][1];
	point.z = world_centr.x * invert_matrix[0][2] + world_centr.y * invert_matrix[1][2] + world_centr.z * invert_matrix[2][2] + invert_matrix[3][2];
	w = world_centr.x * invert_matrix[0][3] + world_centr.y * invert_matrix[1][3] + world_centr.z * invert_matrix[2][3] + invert_matrix[3][3];
	if (w != 0 && w != 1)
	{
		point.x = (point.x + 1) / w;
		point.y = (point.y + 1) / w;
		point.z = (point.z + 1) / w;
	}
	return (point);
}

void	refresh_obj(const t_matrix *camera, t_obj *obj)
{
	t_v3d	point;
	t_sphere *tmp = (t_sphere*)obj->data;
	if (obj->flag == sphere)
	{
		point = mult_vect_matrix(tmp->world_centr, camera->invert_matrix);
		((t_sphere*)obj->data)->cam_centr = point;
		//printf("\n%f, %f, %f\n", point.x, point.y, point.z);
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
		camera->matrix[3][1] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_S])
	{
		camera->matrix[3][1] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_A])
	{
		camera->matrix[3][0] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_D])
	{
		camera->matrix[3][0] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_SPACE])
	{
		camera->matrix[3][2] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_LCTRL])
	{
		camera->matrix[3][2] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
}

void		ft_render(t_sdl *sdl, t_obj *obj)
{
	SDL_Surface *canvas = NULL;
	SDL_Texture *screen = NULL;
	t_time		time;
	memset(&time, 0, sizeof(t_time));
	canvas = new_canvas(sdl->screen_size.x, sdl->screen_size.y);

	t_camera*	camera = NULL;

	camera = make_camera(0);
	//invert_matrix(camera);
	//refresh_obj(camera, obj);


	while (sdl->loop)
	{
		invert_matrix(camera->cam);
		refresh_obj(camera->cam, obj);

		//memset(canvas->pixels, 0, sdl->screen_size.x * sdl->screen_size.y);
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		if (sdl->event.type == SDL_QUIT)
			sdl->loop = 0;
		if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
			sdl->loop = 0;
		time_tick(&time);
		move_camera(sdl->cur_key, camera->cam, &time);

		ft_draw(sdl, canvas, obj, camera);
		screen = SDL_CreateTextureFromSurface(sdl->renderer, canvas);
		memset(canvas->pixels, 0, sizeof(uint32_t) * 640 * 480);
		SDL_RenderCopy(sdl->renderer, screen, 0, 0);
		SDL_RenderPresent(sdl->renderer);

		SDL_RenderClear(sdl->renderer);
		SDL_DestroyTexture(screen);
	}
	destroy_camera(&camera);
	//destroy_matrix(&camera);
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

	//t_matrix *demo = get_new_matrix(3);
	//demo->matrix[0][0] = 0.0;
	//	demo->matrix[0][1] = 1.0;
	//		demo->matrix[0][2] = 0.0;
	//demo->matrix[1][0] = 0.0;
	//	demo->matrix[1][1] = 0.0;
	//		demo->matrix[1][2] = 1.0;
	//demo->matrix[2][0] = 25.0;
	//	demo->matrix[2][1] = 0.0;
	//		demo->matrix[2][2] = 50.0;

	//invert_matrix(demo);

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
