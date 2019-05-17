#include "main.h"

void		ft_split_del(char **head)
{
	int8_t	i;

	i = 0;
	while (head[i])
	{
		free(head[i]);
		head[i] = NULL;
		i++;
	}
	free(head);
	head = NULL;
}
void		push_back_list(const char *line, t_list **des)
{
	t_list *tmp;

	if (!line || !des)
		return;
	if (!*des)
	{
		*des = ft_lstnew(line, ft_strlen(line));
		return;
	}
	tmp = *des;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			tmp->next = ft_lstnew(line, ft_strlen(line));
			return;
		}
		tmp = tmp->next;
	}
}
void		push_back_light(t_light *src, t_light **des)
{
	t_light *tmp;

	if (!src || !des)
		return ;
	if (!*des)
	{
		*des = src;
		return;
	}
	tmp = *des;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			tmp->next = src;
			return;
		}
		tmp = tmp->next;
	}
}
void		push_back_obj(t_obj *src, t_obj **des)
{
	t_obj	*tmp;

	if (!src || !des)
		return;
	if (!*des)
	{
		*des = src;
		return;
	}
	tmp = *des;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			tmp->next = src;
			return;
		}
		tmp = tmp->next;
	}
}
void		color_move(int *color, int up)
{
	if (up)
		(*color)++;
	if ((*color) < 0)
		(*color) = 0;
	if ((*color) > 255)
		(*color) = 0;
}
void		fs_double_swap(double_t *s, double_t *d)
{
	double_t t;

	t = *s;
	*s = *d;
	*d = t;
}
uint32_t	set_pixel_color(t_rgb color, double_t tone)
{
	//hitColor = std::max(0.f, hitNormal.dotProduct(-dir)); // facing ratio 
	double_t	shadow = tone < 0.0 ? 0.0 : tone;

	uint32_t	result;
	t_v3d		tmp;

	tmp.x = color.r;
	tmp.y = color.g;
	tmp.z = color.b;


	if (tmp.x * shadow > tmp.x)
		tmp.x = color.r;
	else if (tmp.x * shadow < 0)
		tmp.x = 0.0;
	else
		tmp.x *= shadow;

	if (tmp.y * shadow > tmp.y)
		tmp.y = color.g;
	else if (tmp.y * shadow < 0)
		tmp.y = 0.0;
	else
		tmp.y *= shadow;

	if (tmp.z * shadow > tmp.z)
		tmp.z = color.b;
	else if (tmp.z * shadow < 0)
		tmp.z = 0.0;
	else
		tmp.z *= shadow;


	result = ((uint8_t)tmp.x << 16 | (uint8_t)tmp.y << 8 | (uint8_t)tmp.z);
	return (result);
}
uint32_t	set_pixel_color_with_hit_color(t_rgb color, t_hit *hit, t_light *light, t_ray *ray)
{
	t_rgb		result = get_black_color();
	t_v3d		tmp;
	double_t	dist = vec_3magnitude(vec_3sub(light->cam_pos, hit->point_hit));

	double_t	t = light->power_light / dist;

	double_t	tone = vec_3dot(get_to_light_dir(hit, light), hit->norml_hit) * t;
	double_t cof = 0.18;
	t_v3d v1 = vec_3norm(vec_3sub(hit->point_hit, ray->orig));
	t_v3d v2 = vec_3norm(vec_3sub(light->cam_pos, hit->point_hit));
	t_v3d v3 = vec_3norm(vec_reflect(v2, hit->norml_hit));
	double_t ttt = vec_3dot(v1, v3) * -tone * 2;

	//----------------------- ambient lighting
	result = colort_mult_f(color, 0.18);
	//----------------------- diffuse lighting
	result = colort_add_colort(result, colort_mult_f(color, tone));
	//----------------------- specular lighting
	result = colort_add_colort(result, colort_mult_f(light->color, tone));
	//-----------------------

	//result = colort_add_colort(result, colort_mult_f(light->color, ttt));

	//result = colort_add_colort(colort_mult_f(light->color, tone), result);


	//t_rgb		clr_light = colort_mult_f(light->color, t);


	//tone = tone < 0 ? 0 : tone;

	//tmp.x = (color.r * tone) > 255 ? 255 : color.r * tone;
	//tmp.y = (color.g * tone) > 255 ? 255 : color.g * tone;
	//tmp.z = (color.b * tone) > 255 ? 255 : color.b * tone;

	//tmp.x = (tmp.x + clr_light.r * tone) > 255 ? 255 : tmp.x + clr_light.r * tone;
	//tmp.y = (tmp.y + clr_light.g * tone) > 255 ? 255 : tmp.y + clr_light.g * tone;
	//tmp.z = (tmp.z + clr_light.b * tone) > 255 ? 255 : tmp.z + clr_light.b * tone;


	//tmp.x = (color.r * sun) > 255 ? 255 : color.r * sun;
	//tmp.y = (color.g * sun) > 255 ? 255 : color.g * sun;
	//tmp.z = (color.b * sun) > 255 ? 255 : color.b * sun;
	
	//tmp.y = color.g * tone;
	//tmp.z = color.b * tone;

	//result = ((uint8_t)tmp.x << 16 | (uint8_t)tmp.y << 8 | (uint8_t)tmp.z);
	return (result.color);
}
