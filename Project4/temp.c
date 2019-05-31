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
void		fs_double_swap(double_t *s, double_t *d)
{
	double_t t;

	t = *s;
	*s = *d;
	*d = t;
}
uint32_t	set_pixel_color_with_hit_color(t_rgb color, t_hit *hit, t_light *light, t_ray *ray)
{
	t_rgb		result; 
	double_t	dist; 
	double_t	dist_cof; 
	double_t	lambert_cof; 
	t_rgb		light_color;

	result = get_black_color();
	dist = vec_3magnitude(vec_3sub(light->cam_pos, hit->point_hit));
	dist_cof = light->power_light / dist;
	lambert_cof = vec_3dot(get_to_light_dir(hit, light), hit->norml_hit) * dist_cof;
	result = colort_mult_f(color, lambert_cof);
	light_color = colort_mult_f(light->color, (dist_cof * lambert_cof));
	set_rgb_to_int(&light_color);
	result = colort_add_colort(result, light_color);
	return (result.color);
}
