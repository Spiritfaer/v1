#include "main.h"

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

int8_t		ft_trace(t_hit *hit, t_obj *index_obj, t_ray *ray)
{
	double_t	bias = 1; // befor I used 1, but now I can't see diferens, hm....
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
		//Vec3f hitPoint = orig + dir * t; I use tNear, it's meen the same, in this case;
		hit->point_hit = vec_3add(ray->orig, vec_3fmul(ray->dir, hit->tNear));
		hit->norml_hit = hit->hit_obj->get_n_hit(&hit->point_hit, hit->hit_obj);
		//-------------------------
		hit->point_hit = vec_3add(hit->point_hit, vec_3fmul(hit->norml_hit, bias));
		//-------------------------
		return (true);
	}
	else
		return (false);
}

t_obj			*old_ft_trace(t_obj *obj, t_ray *ray, t_hit *hit)
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
	if (hit->tNear < DBL_MAX && (hit->tNear < 200.0 || hit->tNear > -200.0))
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

t_rgb			cast_ray(const t_sdl *sdl, t_scena *scena, t_ray *ray, int16_t depth)
{
	t_obj		*index_obj = scena->obj_list;
	uint32_t	pix;
	t_hit		hit;
	t_rgb		color;
	t_rgb		reflect_color;
	t_ray		reflect;

	if (depth++ >= MAX_DEPTH)
		return (colort_mult_f(scena->camera_point->bg_color, 0.18));

	if (ft_trace(&hit, scena->obj_list, ray))
	{

		hit.color_hit.color = set_pixel_color_with_hit_color(hit.hit_obj->get_color(hit.hit_obj->data), &hit, scena->light_list, ray);
		set_int_to_rgb(&hit.color_hit);

		if (hit.hit_obj->flag == sphere)
		{
			reflect.dir = vec_3dreflect(ray->dir, hit.norml_hit);
			reflect.orig = hit.point_hit;
			reflect.type = ReflectionAndRefraction;

			if (ray->type == ReflectionAndRefraction)
			{
				hit.color_hit = colort_mult_f(hit.color_hit, 0.18);
			}
			color = colort_add_colort(cast_ray(sdl, scena, &reflect, depth + 1), hit.color_hit);
		}
		else
			color = hit.hit_obj->get_color(hit.hit_obj->data);
		return (color);
	}
	else
	{
		if (ray->type == primary)
			return (scena->camera_point->bg_color);
		else
			return (colort_mult_f(scena->camera_point->bg_color, 0.18));
	}



	/*
	tmp_obj = old_ft_trace(scena->obj_list, ray, &hit);
	if (tmp_obj)
	{
		//t_v3d reflect = vec_reflect(ray->dir, hit.norml_hit);
		t_v3d dir_to_light = get_to_light_dir(&hit, scena->light_list);
		if (shadow_ray(scena->obj_list, &hit, &dir_to_light))
		{
			pix = set_pixel_color_with_hit_color(tmp_obj->get_color(tmp_obj->data), &hit, scena->light_list, ray);
			//print_v3d(&hit.point_hit, "point hit = ");
		}
		else
			pix = scena->camera_point->bg_color.color;
		
		return (pix);
	}
	*/
	/*return (scena->camera_point->bg_color.color);*/
}


static void		set_var_to_draw_foo(t_ray *ray, t_v3d *point, t_v2i *i)
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
			//tmp[i.x + i.y * sdl->screen_size.x] = 0xA3C6C0;
			i.y++;
		}
		i.x++;
	}
	scena->camera_point->on = false;
}

void			post_mix(SDL_Surface *canvas, t_v2i size)
{
	int32_t x;
	int32_t y;
	uint32_t *tmp = (uint32_t*)canvas->pixels;
	uint32_t *buff;
	uint32_t b[5];
	
	buff = (uint32_t*)malloc(sizeof(uint32_t)* size.x * size.y);

	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			b[0] = *(tmp + x + y * size.x);
			if ((x - 1) > 0)
				b[1] = colort_int_add_colort_int(b[0], *(tmp + (x - 1) + y * size.x));
			if ((x + 1) < size.x)
				b[2] = colort_int_add_colort_int(b[0], *(tmp + (x + 1) + y * size.x));
			if ((y - 1) > 0)
				b[3] = colort_int_add_colort_int(b[0], *(tmp + x + (y - 1) * size.x));
			if ((y + 1) < size.y)
				b[4] = colort_int_add_colort_int(b[0], *(tmp + x + (y + 1) * size.x));
			//-------------
			*(buff + x + y * size.x) = colort_int_add_colort_int(colort_int_add_colort_int(colort_int_add_colort_int(b[0], b[1]), colort_int_add_colort_int(b[2], b[3])), b[4]);
			//-------------

			//*(buff + x + y * size.x) = b[0] + b[1] + b[2] + b[3] + b[4];
			y++;
		}
		x++;
	}
	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			*(tmp + x + y * size.x) = *(buff + x + y * size.x);
			y++;
		}
		x++;
	}
	free(buff);
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
			post_mix(sdl->canvas, sdl->screen_size);
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
