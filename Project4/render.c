#include "main.h"

t_obj		*ft_trace(t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_obj	*tmp;
	double_t bias = 1;
	
	tmp = NULL;
	hit->tNear = DBL_MAX;
	while (obj)
	{
		hit->t = DBL_MAX;
		if (obj->intersect(ray, obj->data, &hit->t) != 0 && hit->t < hit->tNear)
		{
			hit->tNear = hit->t;
			tmp = obj;
		}
		obj = obj->next;
	}
	hit->t = hit->tNear;
	if (hit->tNear < DBL_MAX)
	{
		//Vec3f hitPoint = orig + dir * t;
		hit->point_hit = vec_3add(ray->orig, vec_3fmul(ray->dir, hit->t));
		hit->norml_hit = tmp->get_n_hit(&hit->point_hit, tmp);
		//-------------------------

		hit->point_hit = vec_3add(hit->point_hit, vec_3fmul(hit->norml_hit, bias));
		//-------------------------
		return (tmp);
	}
	return (NULL);
}

int8_t			shadow_ray(t_obj *obj, t_hit *hit, t_v3d *dir_to_light)
{
	double_t tmp;
	t_ray shadow_ray;

	shadow_ray.orig = hit->point_hit;
	shadow_ray.dir = *dir_to_light;

	while (obj)
	{
		if (obj->intersect(&shadow_ray, obj->data, &tmp))
			return (false);
		obj = obj->next;
	}
	return (true);
}

uint32_t		cast_ray(const t_sdl *sdl, t_scena *scena, t_ray *ray)
{
	const t_obj	*tmp_obj;
	uint32_t	pix;
	t_hit		hit;


	tmp_obj = ft_trace(scena->obj_list, ray, &hit);
	if (tmp_obj)
	{
		//t_v3d reflect = vec_reflect(ray->dir, hit.norml_hit);
		t_v3d dir_to_light = get_to_light_dir(&hit, scena->light_list);
		if (shadow_ray(scena->obj_list, &hit, &dir_to_light))
			pix = set_pixel_color_with_hit_color(tmp_obj->get_color(tmp_obj->data), &hit, scena->light_list);
		else
			pix = 0x000000;
		
		return (pix);
	}

	return (BG_COLOR);
}

static void set_var_to_draw_foo(t_ray *ray, t_v3d *point, t_v2i *i)
{
	memset(ray, 0, sizeof(t_ray));
	memset(point, 0, sizeof(t_v3d));
	point->z = -1;
	memset(i, 0, sizeof(t_v2i));
}
void	ft_draw(const t_sdl *sdl, t_scena *scena)
{
	t_ray		ray;
	t_v3d		point;
	t_v2i		i;

	uint32_t	*tmp = (uint32_t*)sdl->canvas->pixels;
	set_var_to_draw_foo(&ray, &point, &i);
	ray.orig = mult_vect_matrix_4_4(vec_1zero(), scena->camera_point->cam->matrix);
	while (i.x < sdl->screen_size.x)
	{
		i.y = 0;
		while (i.y < sdl->screen_size.y)
		{
			point.x = (CANVAS_SIZE * (i.x + 0.5) / (double_t)(sdl->screen_size.x) - 1) * sdl->iar * scena->camera_point->scale;
			point.y = (1 - CANVAS_SIZE * (i.y + 0.5) / (double_t)(sdl->screen_size.y)) * scena->camera_point->scale;
			ray.dir = mult_vect_matrix_3_3(point, (scena->camera_point->cam->invert_matrix));
			vec_3normalize(&ray.dir);
			tmp[i.x + i.y * sdl->screen_size.x] = cast_ray(sdl, scena, &ray);
			//tmp[i.x + i.y * sdl->screen_size.x] = 0xA3C6C0;
			i.y++;
		}
		i.x++;
	}
	scena->camera_point->on = false;
}

void			refresh_obj(const t_matrix *camera, t_obj *obj, t_light *light)
{
	while (light)
	{
		light->cam_pos = mult_vect_matrix_3_3(light->pos , camera->invert_matrix);
		light = light->next;
	}
	while (obj)
	{
		obj->to_camera(camera, obj->data);
		obj = obj->next;
	}
}
void			ft_render(t_sdl *sdl, t_scena *scena)
{
	SDL_Texture *screen = NULL;
	t_time		time;

	//scena->camera_point = make_camera(0);
	memset(&time, 0, sizeof(t_time));
	while (sdl->loop)
	{
		if (scena->camera_point->on > false)
		{
			invert_matrix(scena->camera_point->cam);
			refresh_obj(scena->camera_point->cam, scena->obj_list, scena->light_list);
			memset(sdl->canvas->pixels, 0, sizeof(uint32_t) * WIN_SIZE_W * WIN_SIZE_H);
			ft_draw(sdl, scena);
			screen = SDL_CreateTextureFromSurface(sdl->renderer, sdl->canvas);
			SDL_RenderCopy(sdl->renderer, screen, 0, 0);
			SDL_DestroyTexture(screen);
			scena->camera_point->on = false;
		}
		event_guard(sdl, scena->camera_point, &time);
		SDL_RenderPresent(sdl->renderer);
	}
	print_matrix(scena->camera_point->cam->matrix, scena->camera_point->cam->size);
	//destroy_camera(&scena->camera_point);
	SDL_FreeSurface(sdl->canvas);
}
