#include "main.h"

int8_t		pars_pos(const char *str, t_v3d *pos)
{
	int8_t	i;
	char	**split;

	i = 1;
	if (ft_splitter(str, ' ') != 4)
		return (false);
	split = ft_strsplit(str, ' ');
	pos->x = ft_atof(split[1]);
	pos->y = ft_atof(split[2]);
	pos->z = ft_atof(split[3]);
	ft_split_del(split);
	return (true);
}

int8_t		pars_color(const char *str, t_rgb *color)
{
	int8_t	i;
	char	**split;

	i = 1;
	if (ft_splitter(str, ' ') != 4)
		return (false);
	split = ft_strsplit(str, ' ');
	color->r = ft_atoi(split[1]);
	color->g = ft_atoi(split[2]);
	color->b = ft_atoi(split[3]);
	set_rgb_to_int(color);
	ft_split_del(split);
	return (true);
}

int8_t		pars_size_fov_power(const char *str, double_t *src)
{
	int8_t	i;
	char	**split;

	i = 1;
	if (ft_splitter(str, ' ') != 2)
		return (false);
	split = ft_strsplit(str, ' ');
	*src = ft_atof(split[1]);
	ft_split_del(split);
	return (true);
}

int8_t		pars_info(t_list *list, t_rgb *color, t_v3d *pos, double_t *size, double_t *reflection)
{
	int8_t	i;

	i = 4;
	list = list->next;
	while (i--)
	{
		if (ft_strnequ(list->content, "pos:", 4))
			pars_pos(list->content, pos);
		else if (ft_strnequ(list->content, "color:", 6))
			pars_color(list->content, color);
		else if (ft_strnequ(list->content, "size:", 5))
			pars_size_fov_power(list->content, size);
		else if (ft_strnequ(list->content, "fov:", 4))
			pars_size_fov_power(list->content, size);
		else if (ft_strnequ(list->content, "bg:", 3))
			pars_color(list->content, color);
		else if (ft_strnequ(list->content, "power:", 6))
			pars_size_fov_power(list->content, size);
		else if (ft_strnequ(list->content, "reflection:", 11))
			pars_size_fov_power(list->content, reflection);
		list = list->next;
	}
	return (true);
}

void		pars_type_obj(t_scena *scena)
{
	t_rgb		color;
	t_v3d		pos;
	double_t	size;
	double_t	reflection;
	t_list		*tmp;

	tmp = scena->head_list;
	while (tmp)
	{
		if (ft_strnequ(tmp->content, "type:", 5))
		{
			pars_info(tmp, &color, &pos, &size, &reflection);
			if (ft_strnequ((((unsigned char*)tmp->content) + 6), "sphere;", 7))
				push_back_obj(ft_new_sphere(pos, color, size, reflection), &scena->obj_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "plane;", 6))
				push_back_obj(ft_new_plane(pos, color, size, plane, reflection), &scena->obj_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "disk;", 6))
				push_back_obj(ft_new_plane(pos, color, size, disk, reflection), &scena->obj_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "box;", 4))
				push_back_obj(ft_new_box(&pos, NULL, color, size, reflection), &scena->obj_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "cone;", 5))
				push_back_obj(ft_new_cone(pos, color, size), &scena->obj_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "point_light;", 12))
				push_back_light(new_light(&pos, &color, size), &scena->light_list);
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "camera;", 7))
				scena->camera_point = new_camera(&pos, &color, size);
			else
				write(1, "error!\n", 7);
		}
		tmp = tmp->next;
	}
}

int8_t		pars_file(const char *file_name, t_scena *scena)
{
	int32_t	fd;
	char	*line;

	line = NULL;
	if ((fd = open(file_name, _O_TEXT)) == -1)
		return (false);
	while (get_next_line(fd, &line))
	{
		push_back_list(line, &scena->head_list);
		free(line);

	}
	close(fd);
	return (true);
}

int8_t		new_scena(const char *file_name, t_scena *scena)
{
	if (!pars_file(file_name, scena))
		return (false);

	pars_type_obj(scena);
	return (true);
}
