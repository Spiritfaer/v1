#include "main.h"

SDL_Surface *new_canvas(uint32_t width, uint32_t height)
{
	SDL_Surface *new_surf;
	new_surf = SDL_CreateRGBSurface(0, width, height, 32,
		0, 0, 0, 0);
	return (new_surf);
}

uint32_t	set_pixel_color(t_rgb color, double_t shadow)
{
	uint32_t	result;
	t_v3d		tmp;

	tmp.x = color.r;
	if (tmp.x * shadow > tmp.x)
		tmp.x = 0.0;
	else if (tmp.x * shadow < 0)
		tmp.x = 0.0;
	else
		tmp.x *= shadow;
	tmp.y = color.g;
	if (tmp.y * shadow > tmp.y)
		tmp.y = 0.0;
	else if (tmp.y * shadow < 0)
		tmp.y = 0.0;
	else
		tmp.y *= shadow;
	tmp.z = color.b;
	if (tmp.z * shadow > tmp.z)
		tmp.z = 0.0;
	else if (tmp.z * shadow < 0)
		tmp.z = 0.0;
	else
		tmp.z *= shadow;

	result = ((uint8_t)tmp.x << 16 | (uint8_t)tmp.y << 8 | (uint8_t)tmp.z);
	return (result);
}

t_v3d		vec_3invert(const t_v3d *src)
{
	t_v3d dest;

	dest.x = -src->x;
	dest.y = -src->y;
	dest.z = -src->z;
	return (dest);
}

uint8_t		cast_ray(const t_sdl *sdl, const t_obj *obj, t_v3d *orig, t_v3d *dir, t_v2i i, SDL_Surface *canvas)
{
	const t_obj		*tmp_obj;
	double_t	tNear;
	double_t	t;
	uint32_t	*tmp = (uint32_t*)canvas->pixels;
	t_v3d		point_hit;
	t_v3d		n_hit;
	double_t	shadow;

	uint8_t result = false;
	tmp_obj = obj;
	tNear = DBL_MAX;
	while (tmp_obj)
	{
		t = DBL_MAX;
		if (tmp_obj->intersect(orig, dir, tmp_obj->data, &t) != 0 && t < tNear)
		{
			tNear = t;
			//Vec3f hitPoint = orig + dir * t;----------------
			point_hit = vec_3add(*orig, vec_3fmul(*dir, t));
			n_hit = vec_3sub(point_hit, tmp_obj->get_center(tmp_obj->data));
			vec_3normalize(&n_hit);
			shadow = vec_3dot(n_hit, vec_3invert(dir));
			tmp[i.x + i.y * sdl->screen_size.x] = set_pixel_color(tmp_obj->get_color(tmp_obj->data), shadow);
			result = true;
		}
		tmp_obj = tmp_obj->next;
	}
	return (result);
}

static void set_var_to_draw_foo(t_v3d *orig, t_v3d *dir, t_v3d *point, t_v2i *i)
{
	memset(orig, 0, sizeof(t_v3d));
	memset(dir, 0, sizeof(t_v3d));
	memset(point, 0, sizeof(t_v3d));
	point->z = -DISTANCE_TO_CANVAS;
	memset(i, 0, sizeof(t_v2i));
}
void	ft_draw(const t_sdl *sdl, SDL_Surface *canvas, const t_obj *obj, t_camera *camera)
{
	t_v3d		orig;
	t_v3d		dir;
	t_v3d		point;
	t_v2i		i;

	uint32_t	*tmp	= (uint32_t*)canvas->pixels;
	set_var_to_draw_foo(&orig, &dir, &point, &i);
	orig = mult_vect_matrix_4_4((t_v3d){0,0,0}, camera->cam->matrix);
	while (i.x < sdl->screen_size.x)
	{
		i.y = 0;
		while (i.y < sdl->screen_size.y)
		{
			point.x = (CANVAS_SIZE * (i.x + 0.5) / (double_t)(sdl->screen_size.x) - 1) * sdl->iar * camera->scale;
			point.y = (1 - CANVAS_SIZE * (i.y + 0.5) / (double_t)(sdl->screen_size.y)) * camera->scale;
			dir = mult_vect_matrix_3_3(point, (camera->cam->invert_matrix));
			vec_3normalize(&dir);
			if (cast_ray(sdl, obj, &orig, &dir, i, canvas) == 0)
			{
				tmp[i.x + i.y * sdl->screen_size.x] = 0xA3C6C0;
			}
			i.y++;
		}
		i.x++;
	}
	camera->on = false;
}

void	refresh_obj(const t_matrix *camera, t_obj *obj)
{
	t_v3d	point;
	t_v3d	normal;
	t_sphere *sph;
	t_plane *pl;
	t_box *b;
	while (obj)
	{
		if (obj->flag == sphere)
		{
			sph = (t_sphere*)obj->data;
			point = mult_vect_matrix_3_3(sph->world_centr, camera->invert_matrix);
			((t_sphere*)obj->data)->cam_centr = point;
		}
		else if (obj->flag == plane || obj->flag == disk)
		{
			pl = (t_plane*)obj->data;
			point = mult_vect_matrix_3_3(pl->world_centr, camera->invert_matrix);
			normal = mult_vect_matrix_3_3(pl->world_normal, camera->invert_matrix);
			vec_3normalize(&normal);
			((t_plane*)obj->data)->cam_centr = point;
			((t_plane*)obj->data)->cam_normal = normal;
		}
		else if (obj->flag == box)
		{
			b = (t_box*)obj->data;
			b->cam_min = mult_vect_matrix_3_3(b->min, camera->invert_matrix);
			b->cam_max = mult_vect_matrix_3_3(b->max, camera->invert_matrix);
		}
		obj = obj->next;
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
		if (camera->on > false)
		{
			invert_matrix(camera->cam);
			refresh_obj(camera->cam, obj);
			memset(canvas->pixels, 0, sizeof(uint32_t) * 640 * 480);
			ft_draw(sdl, canvas, obj, camera);
			screen = SDL_CreateTextureFromSurface(sdl->renderer, canvas);
			SDL_RenderCopy(sdl->renderer, screen, 0, 0);
			SDL_DestroyTexture(screen);
			camera->on = false;
		}
		event_guard(sdl, camera, &time);
		SDL_RenderPresent(sdl->renderer);
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
	t_v3d		centr2;
	t_rgb		color;
	double_t	radius;
	int32_t		q = 3;

	sdl = ft_new_sdl();
	
	ft_temp_fill(&centr, &color, &radius, sdl->screen_size);
	obj = ft_new_sphere(centr, color, radius);

	centr = vec_3d(-2.0, 3.0, -1.5);
	set_color(&color, 33, 66, 30);
	radius = 1.5 * q;
	push_back_obj(ft_new_sphere(centr, color, radius), obj);

	centr = vec_3d(5.0, 7.0, 1.0);
	set_color(&color, 83, 55, 122);
	radius = 0.7 * q;
	push_back_obj(ft_new_sphere(centr, color, radius), obj);

	centr = vec_3d(5.0, 7.0, -0.5);
	set_color(&color, 255, 255, 255);
	radius = 1 * q;
	push_back_obj(ft_new_sphere(centr, color, radius), obj);

	centr = vec_3d(0.0, -5.5, -20.5);
	set_color(&color, 200, 200, 25);
	radius = 5 * q;
	push_back_obj(ft_new_plane(centr, color, radius, disk), obj);

	centr = (t_v3d) { 1, 1, 1 };
	centr2 = (t_v3d) { -1, -1, -1 };
	set_color(&color, 35, 75, 150);
	push_back_obj(ft_new_box(&centr, &centr2, color), obj);

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
