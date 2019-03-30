#include "main.h"


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
			shadow = vec_3dot(n_hit, vec_3invert_dir(dir));
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

	uint32_t	*tmp = (uint32_t*)canvas->pixels;
	set_var_to_draw_foo(&orig, &dir, &point, &i);
	orig = mult_vect_matrix_4_4((t_v3d) { 0, 0, 0 }, camera->cam->matrix);
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
