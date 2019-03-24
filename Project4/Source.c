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
	t_v3d		orig	= { 0, 0, 0 };
	t_v3d		dir = /*camera->matrix*/ { 0, 0, 0 };
	t_v3d		ray = { 0,0,-1 };
	double_t	t		= DBL_MAX;
	uint32_t	*tmp	= (uint32_t*)canvas->pixels;
	int32_t count = 0;
	double_t imageAspectRatio = (double_t)(sdl->screen_size.x) / (double_t)(sdl->screen_size.y);
	double_t scale = tan(deg_to_rad(camera->fov * 0.5));

	t_v2i i = { 0,0 };

	orig = mult_vect_matrix_4_4((t_v3d){0,0,0}, camera->cam->matrix);
	while (i.x < sdl->screen_size.x)
	{
		i.y = 0;
		while (i.y < sdl->screen_size.y)
		{
			ray.x = (2 * (i.x + 0.5) / (double_t)(sdl->screen_size.x) - 1) * imageAspectRatio * scale;
			ray.y = (1 - 2 * (i.y + 0.5) / (double_t)(sdl->screen_size.y)) * scale;
			dir = mult_vect_matrix_3_3(ray, (camera->cam->invert_matrix));
			vec_3normalize(&dir);
			//if (obj->intersect(&orig, &dir, (t_sphere*)obj->data, &t) && t > 0)
			//{
			//	tmp[orig.x + orig.y * sdl->screen_size.x] = ((t_sphere*)obj->data)->color.color;
			//}
			if (sphere_intersect(&orig, &dir, (t_sphere*)obj->data, &t) != 0 && t > 0)
					tmp[i.x + i.y * sdl->screen_size.x] = ((t_sphere*)obj->data)->color.color;
				//((uint32_t*)canvas->pixels)[x + y * sdl->screen_size.x] = 0xFFFFFF;
			//Vec3f hitPoint = orig + dir * t;
			else
				tmp[i.x + i.y * sdl->screen_size.x] = 0x3914AF;
			i.y++;
		}
		i.x++;
	}
}

t_camera*	make_camera(int32_t size)
{
	t_camera *camera;

	if ((camera = (t_camera*)malloc(sizeof(t_camera))) == NULL)
		return (NULL);
	memset(camera, 0, sizeof(t_camera));
	camera->fov = 90;
	if (size == 0)
	{
		camera->cam = get_new_matrix(4);
		fill_vertical_matrix(camera->cam);
		camera->cam->matrix[3][2] = 25;
		camera->cam->matrix[3][0] = 0;
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

void	refresh_obj(const t_matrix *camera, t_obj *obj)
{
	t_v3d	point;
	t_sphere *tmp = (t_sphere*)obj->data;
	if (obj->flag == sphere)
	{
		point = mult_vect_matrix_4_4(tmp->world_centr, camera->invert_matrix);
		((t_sphere*)obj->data)->cam_centr = point;
		//printf("\n%f, %f, %f\n", point.x, point.y, point.z);
	}
}

void			ft_render(t_sdl *sdl, t_obj *obj)
{
	SDL_Surface *canvas = NULL;
	SDL_Texture *screen = NULL;
	t_camera*	camera = NULL;
	t_time		time;

	camera = make_camera(0);
	memset(&time, 0, sizeof(t_time));
	canvas = new_canvas(sdl->screen_size.x, sdl->screen_size.y);

	while (sdl->loop)
	{
		invert_matrix(camera->cam);
		refresh_obj(camera->cam, obj);
		event_guard(sdl, camera, &time);
		ft_draw(sdl, canvas, obj, camera);

		screen = SDL_CreateTextureFromSurface(sdl->renderer, canvas);
		memset(canvas->pixels, 0, sizeof(uint32_t) * 640 * 480);

		SDL_RenderCopy(sdl->renderer, screen, 0, 0);
		SDL_RenderPresent(sdl->renderer);

		SDL_RenderClear(sdl->renderer);
		SDL_DestroyTexture(screen);
	}
	destroy_camera(&camera);
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
