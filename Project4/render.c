#include "main.h"
/*
Vec3f castRay(
	const Vec3f &orig, const Vec3f &dir,
	const std::vector<std::unique_ptr<Object>> &objects,
	const std::unique_ptr<DistantLight> &light,
	const Options &options)
{
	Vec3f hitColor = options.backgroundColor;
	float tnear = kInfinity;
	Vec2f uv;
	uint32_t index = 0;
	Object *hitObject = nullptr;
	if (trace(orig, dir, objects, tnear, index, uv, &hitObject)) {
		Vec3f hitPoint = orig + dir * tnear;
		Vec3f hitNormal;
		Vec2f hitTexCoordinates;
		hitObject->getSurfaceProperties(hitPoint, dir, index, uv, hitNormal, hitTexCoordinates);
		Vec3f L = -light->dir;
		// compute color of diffuse surface illuminated
		// by a single distant light source.
		hitColor = hitObject->albedo / M_PI * light->intensity * light->color * std::max(0.f, hitNormal.dotProduct(L));
	}

	return hitColor;
}
*/

int8_t		trace(t_scena *scena, t_ray *ray, t_hit *hit)
{
	const t_obj	*tmp_obj;

	tmp_obj = scena->obj_list;
	while (tmp_obj)
	{
		if (tmp_obj->intersect(ray, tmp_obj->data, &hit->t) != 0 && hit->t < hit->tNear)
			return (true);
		tmp_obj = tmp_obj->next;
	}
	return (false);
}

uint8_t		cast_ray(const t_sdl *sdl, t_scena *scena, t_ray *ray, t_v2i i)
{
	const t_obj	*tmp_obj;
	uint32_t	*tmp;
	t_hit		hit;

	uint8_t result = false;
	tmp = (uint32_t*)sdl->canvas->pixels;
	tmp_obj = scena->obj_list;
	hit.tNear = DBL_MAX;



	while (tmp_obj)
	{
		hit.t = DBL_MAX;
		if (tmp_obj->intersect(ray, tmp_obj->data, &hit.t) != 0 && hit.t < hit.tNear)
		{
			hit.tNear = hit.t;
			//Vec3f hitPoint = orig + dir * t;
			hit.point_hit = vec_3add(ray->orig, vec_3fmul(ray->dir, hit.t));
			hit.norml_hit = tmp_obj->get_n_hit(&hit.point_hit, tmp_obj);
			vec_3normalize(&scena->light_list->dir);
			if (!trace(scena, ray, &hit))
			{
				hit.shadow = vec_3dot(hit.norml_hit, scena->light_list->dir);
				hit.shadow = hit.shadow < 0 ? 0 : hit.shadow;
			}
			else
				hit.shadow = 0;
			//hitColor = hitObject->albedo / (PI * suns->intensity * suns->light_color * shadow));
			tmp[i.x + i.y * sdl->screen_size.x] 
				= set_pixel_color(tmp_obj->get_color(tmp_obj->data), 
				(0.18 / PI * scena->light_list->intensity * scena->light_list->light_color * hit.shadow));
			result = true;
		}
		tmp_obj = tmp_obj->next;
	}
	return (result);
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
			if (cast_ray(sdl, scena, &ray, i) == 0)
			{
				tmp[i.x + i.y * sdl->screen_size.x] = 0xA3C6C0;
			}
			i.y++;
		}
		i.x++;
	}
	scena->camera_point->on = false;
}

void			refresh_obj(const t_matrix *camera, t_obj *obj, t_light *light)
{
	t_v3d	point;
	t_v3d	normal;
	t_sphere *sph;
	t_plane *pl;
	t_box *b;
	while (light)
	{
		light->cam_pos = mult_vect_matrix_3_3(light->pos , camera->invert_matrix);
		light = light->next;
	}
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
			ft_set_box_centr((t_box*)obj->data);
		}
		obj = obj->next;
	}
}
void			ft_render(t_sdl *sdl, t_scena *scena)
{
	SDL_Texture *screen = NULL;
	t_time		time;

	scena->camera_point = make_camera(0);
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
	destroy_camera(&scena->camera_point);
	SDL_FreeSurface(sdl->canvas);
}
