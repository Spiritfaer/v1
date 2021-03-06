#include "main.h"

int8_t			ft_trace(t_hit *hit, t_obj *index_obj, t_ray *ray)
{
	double_t	bias = 0.25;
	hit->tNear = DBL_MAX;
	while (index_obj)
	{
		hit->t = DBL_MAX;
		if (index_obj->intersect(ray, index_obj->data, &hit->t) == true && hit->t < hit->tNear)
		{
			hit->tNear = hit->t;
			hit->hit_obj = index_obj;
		}
		index_obj = index_obj->next;
	}
	if (hit->tNear < DBL_MAX)
	{
		hit->point_hit = vec_3add(ray->orig, vec_3fmul(ray->dir, hit->tNear));
		hit->norml_hit = hit->hit_obj->get_n_hit(&hit->point_hit, hit->hit_obj);
		hit->point_hit = vec_3add(hit->point_hit, vec_3fmul(hit->norml_hit, bias));
		return (true);
	}
	else
		return (false);
}
void			cast_var_init(t_hit *hit, t_rgb *color, t_ray *reflect)
{
	ft_memset(hit, 0, sizeof(t_hit));
	ft_memset(color, 0, sizeof(t_rgb));
	ft_memset(reflect, 0, sizeof(t_ray));
}
t_rgb			cast_ray(const t_sdl *sdl, t_scena *scena, t_ray *ray, int16_t depth)
{
	t_obj		*index_obj = scena->obj_list;
	t_light		*index_light = scena->light_list;
	t_hit		hit;
	t_hit		les_hit;
	t_rgb		color;
	t_ray		reflect;
	t_ray		to_light;
	if (depth >= MAX_DEPTH)
		return (scena->camera_point->bg_color);
	cast_var_init(&hit, &color, &reflect);
	les_hit = hit;
	if (ft_trace(&hit, scena->obj_list, ray))
	{
		while (index_light)
		{
			to_light.dir = vec_3sub(index_light->cam_pos, hit.point_hit);
			vec_3normalize(&to_light.dir);
			to_light.orig = hit.point_hit;
			to_light.type = shadow;
			if (!ft_trace(&les_hit, scena->obj_list, &to_light))
			{
				color.color = set_pixel_color_with_hit_color(hit.hit_obj->get_color(hit.hit_obj->data), &hit, index_light, ray);
				set_int_to_rgb(&color);
				hit.color_hit = colort_add_colort(hit.color_hit, color);
			}
			index_light = index_light->next;
		}
		if (hit.hit_obj->get_reflection(hit.hit_obj->data) > 0 || (!color.color && !depth) )
		{
			reflect.dir = vec_3dreflect(ray->dir, hit.norml_hit);
			reflect.orig = hit.point_hit;
			reflect.type = ReflectionAndRefraction;
			if (ray->type == ReflectionAndRefraction)
			{
				hit.color_hit = colort_mult_f(hit.color_hit, 0.18);
			}
			color = colort_add_colort(colort_mult_f(cast_ray(sdl, scena, &reflect, depth + 1),
				hit.hit_obj->get_reflection(hit.hit_obj->data)), hit.color_hit);
		}
		else
			color = hit.color_hit;
		return (color);
	}
	else
		return (scena->camera_point->bg_color);
}
void			set_var_to_draw_foo(t_ray *ray, t_v3d *point, t_v2i *i)
{
	memset(ray, 0, sizeof(t_ray));
	memset(point, 0, sizeof(t_v3d));
	point->z = -1;
	memset(i, 0, sizeof(t_v2i));
}
void			ft_draw(const t_sdl *sdl, t_scena *scena)
{
	t_ray		ray;
	t_v3d		point;
	t_v2i		i;
	t_rgb		pix_color;

	uint32_t	*tmp = (uint32_t*)sdl->canvas->pixels;
	set_var_to_draw_foo(&ray, &point, &i);
	ray.orig = mult_vect_matrix_4_4(vec_1zero(), scena->camera_point->cam->matrix);
	ray.type = primary;
	while (i.x < sdl->screen_size.x)
	{
		i.y = 0;
		while (i.y < sdl->screen_size.y)
		{
			point.x = (CANVAS_SIZE * (i.x + 0.5) / (double_t)(sdl->screen_size.x) - 1) * sdl->iar * scena->camera_point->scale;
			point.y = (1 - CANVAS_SIZE * (i.y + 0.5) / (double_t)(sdl->screen_size.y)) * scena->camera_point->scale;
			ray.dir = mult_vect_matrix_3_3(point, (scena->camera_point->cam->invert_matrix));
			vec_3normalize(&ray.dir);
			pix_color = cast_ray(sdl, scena, &ray, 0);
			tmp[i.x + i.y * sdl->screen_size.x] = pix_color.color;
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
	SDL_FreeSurface(sdl->canvas);
}
