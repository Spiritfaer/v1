#include "main.h"

void	ft_temp_fill(t_v3d *center, t_rgb *color, double_t *radius, t_v2i win_size)
{
	center->x = 5;
	center->y = -3;
	center->z = -1;

	color->r = 255;
	color->g = 117;
	color->b = 20;
	color->color = (color->r << 16 | color->g << 8 | color->b);

	*radius = 1.9;

	/*
	*centr = { 0,0,50 };	
	*color = { 255,0,0,0 };
	*radius = 25.0;
	*/

}

int8_t		pars_file(const char *file_name, t_scena *scena)
{
	int32_t	fd;
	char	*line;

	line = NULL;
	if ((fd = open(file_name, _O_TEXT)) < 0)
		return (false);
	while (get_next_line(fd, &line))
	{
		push_back_list(line, &scena->head_list);
		free(line);
	}
	close(fd);
	return (true);
}

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

int8_t		pars_pos(const char *str, t_v3d *pos)
{
	int8_t	i;
	char	**split;

	i = 1;
	if (ft_splitter(str, ' ') != 4)
		return (false);
	split = ft_strsplit(str, ' ');
	pos->x = ft_atoi(split[1]);
	pos->y = ft_atoi(split[2]);
	pos->z = ft_atoi(split[3]);
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
	*src = ft_atoi(split[1]);
	ft_split_del(split);
	return (true);
}

int8_t		pars_info(t_list *list, t_rgb *color, t_v3d *pos, double_t *size)
{
	int8_t	i;

	i = 3;
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
		list = list->next;
	}
	return (true);
}

t_camera*	new_camera(t_v3d *pos, t_rgb *color, double_t fov)
{
	t_camera *camera;

	if ((camera = (t_camera*)malloc(sizeof(t_camera))) == NULL)
		return (NULL);
	memset(camera, 0, sizeof(t_camera));
	camera->fov = fov;
	camera->on = 1;
	camera->scale = tan(deg_to_rad(camera->fov * 0.5));

	camera->cam = get_new_matrix(4);
	fill_vertical_matrix(camera->cam);
	camera->cam->matrix[3][0] = pos->x;
	camera->cam->matrix[3][1] = pos->y;
	camera->cam->matrix[3][2] = pos->z;
	camera->bg_color = *color;
	return (camera);
}

void		pars_type_obj(t_scena *scena)
{
	t_rgb		color;
	t_v3d		pos;
	double_t	size;
	t_list		*tmp;

	tmp = scena->head_list;
	while (tmp)
	{
		if (ft_strnequ(tmp->content, "type:", 5))
		{
			if (ft_strnequ((((unsigned char*)tmp->content) + 6), "sphere;", 7))
			{
				pars_info(tmp, &color, &pos, &size);
				push_back_obj(ft_new_sphere(pos, color, size), &scena->obj_list);
			}
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "plane;", 6))
			{
				pars_info(tmp, &color, &pos, &size);
				push_back_obj(ft_new_plane(pos, color, size, plane), &scena->obj_list);
			}
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "disk;", 6))
			{
				pars_info(tmp, &color, &pos, &size);
				push_back_obj(ft_new_plane(pos, color, size, disk), &scena->obj_list);
			}
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "box;", 4))
			{
				pars_info(tmp, &color, &pos, &size);
				push_back_obj(ft_new_box(&pos, NULL, color, size), &scena->obj_list);
			}
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "point_light;", 12))
			{
				pars_info(tmp, &color, &pos, &size);
				push_back_light(new_light(&pos, &color, size), &scena->light_list);
			}
			else if (ft_strnequ((((unsigned char*)tmp->content) + 6), "camera;", 7))
			{
				pars_info(tmp, &color, &pos, &size);
				scena->camera_point = new_camera(&pos, &color, size);
			}
			else
				write(1, "info\n", 5);
		}
		tmp = tmp->next;
	}
}

int8_t		new_scena(const char *file_name, t_scena *scena)
{

	if (!pars_file(file_name, scena))
		return (false);
	pars_type_obj(scena);

	//print_list(scena->head_list);
	//centr = vec_3d(-2.0, 3.0, -1.5);
	//set_color(&color, 33, 66, 30);
	//radius = 1.5 * q;
	//push_back_obj(ft_new_sphere(centr, color, radius), &obj);
	return (true);
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

void		print_list(t_list *head)
{
	while (head)
	{
		write(1, head->content, head->content_size);
		write(1, "\n", 1);
		head = head->next;
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
void		print_sdl(t_sdl *sdl)
{
	printf("\n---Point status---\n");
	printf("init flag = %d", sdl->init_flag);
	printf("window = %p\n", sdl->window);
	printf("renderer = %p\n", sdl->renderer);
	printf("cur_key = %p\n", (void*)sdl->cur_key);
	printf("---Other status---\n");
	printf("srceen_size width = %d, height = %d\n", sdl->screen_size.x, sdl->screen_size.y);
	printf("loop = %d\n", sdl->loop);
	printf("win_name = \"%s\"\n", sdl->win_name);
}
void		*sf_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!n || dst == src)
		return (dst);
	while (n-- && ++i)
		*((unsigned char*)dst)++ = *((unsigned char*)src)++;
	return ((unsigned char*)dst - i);
}
void		fill_2(double_t **matrix, int32_t n)
{
	matrix[0][0] = 2.0;
	matrix[0][1] = 5.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -3.0;
}
void		fill_3(double_t **matrix, int32_t n)
{
	matrix[0][0] = 22.0;
		matrix[0][1] = 5.0;
			matrix[0][2] = 7.0;
	matrix[1][0] = 6.0;
		matrix[1][1] = -33.0;
			matrix[1][2] = 4.0;
	matrix[2][0] = 5.0;
		matrix[2][1] = -21.0;
			matrix[2][2] = -3.0;
}
void		fill_4(double_t **matrix, int32_t n)
{
	matrix[0][0] = 22.0;
	matrix[0][1] = 5.0;
	matrix[0][2] = 7.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = -33.0;
	matrix[1][2] = 4.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 5.0;
	matrix[2][1] = -21.0;
	matrix[2][2] = -3.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 25.0;
	matrix[3][1] = -25.0;
	matrix[3][2] = -5.0;
	matrix[3][3] = 1.0;
}
void		fill_random_matrix(double_t **matrix, int32_t n)
{

	if (!matrix || !n)
		return;
	if (n == 2)
		fill_2(matrix, n);
	else if (n == 3)
		fill_3(matrix, n);
	else if (n == 4)
		fill_4(matrix, n);
	else
		printf("ERROR! fill_random_matrix have wrong matrix size!\n");
}
void		print_matrix(double_t **matrix, int32_t n)
{
	t_v2i i;

	i.x = 0;
	while (i.x < n)
	{
		i.y = 0;
		while (i.y < n)
		{
			printf("%10.6f ", matrix[i.x][i.y]);
			i.y++;
		}
		printf("\n");
		i.x++;
	}
	printf("\n");
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

uint32_t	set_pixel_color_with_hit_color(t_rgb color, t_hit *hit, t_light *light)
{
	uint32_t	result;
	t_v3d		tmp;
	double_t	dist = vec_3magnitude(vec_3sub(light->cam_pos, hit->point_hit));
	double_t t = light->power_light / dist;
	double_t	tone = vec_3dot(get_to_light_dir(hit, light), hit->norml_hit) * t;
	//double_t	sun = 0.5;

	tone = tone < 0 ? 0 : tone;
	tmp.x = (color.r * tone) > 255 ? 255 : color.r * tone;
	tmp.y = (color.g * tone) > 255 ? 255 : color.g * tone;
	tmp.z = (color.b * tone) > 255 ? 255 : color.b * tone;
	
	//tmp.x = (color.r * sun) > 255 ? 255 : color.r * sun;
	//tmp.y = (color.g * sun) > 255 ? 255 : color.g * sun;
	//tmp.z = (color.b * sun) > 255 ? 255 : color.b * sun;
	
	//tmp.y = color.g * tone;
	//tmp.z = color.b * tone;

	result = ((uint8_t)tmp.x << 16 | (uint8_t)tmp.y << 8 | (uint8_t)tmp.z);
	return (result);
}
