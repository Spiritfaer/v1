#include "main.h"

void		print_v3d(const t_v3d *src, char *str)
{
	printf("%s.x = %10.4f; %s.y = %10.4f; %s.z = %10.4f;\n", str, src->x, str, src->y, str, src->z);
}
void		print_v3i(const t_v3i *src, char *str)
{
	printf("%s.x = %10d; %s.y = %10d; %s.z = %10d;\n", str, src->x, str, src->y, str, src->z);
}
void		ft_print_color(const t_rgb* color)
{
	printf("Red = %5d; Green = %5d; Blue = %5d;\nINT COLOR = %9d;\n", color->r, color->g, color->b, color->color);
}
void		ft_print_plane(const void *data)
{
	const t_plane* temp;
	temp = data;
	printf("\n---PLANE INFO---\n");
	print_v3d(&temp->world_centr, "world_centr");
	print_v3d(&temp->world_normal, "world_normal");
	ft_print_color(&temp->color);
	printf("------------------\n");
}
void		ft_print_sphere(const void *data)
{
	const t_sphere* temp;
	temp = data;
	printf("\n---SPHERE INFO---\n");
	print_v3d(&temp->world_centr, "world_centr");
	ft_print_color(&temp->color);
	printf("Radius = %6.2f;\n", temp->radius);
	printf("------------------\n");
}
void		ft_print_box(const void *data)
{
	const t_box* temp;
	temp = data;
	printf("\n----BOX INFO----\n");
	print_v3d(&temp->min, "min");
	print_v3d(&temp->max, "min");
	ft_print_color(&temp->color);
	printf("------------------\n");
}
void		ft_print_cone(const void *data) {}
void		print_list(t_list *head)
{
	while (head)
	{
		write(1, head->content, head->content_size);
		write(1, "\n", 1);
		head = head->next;
	}
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
void		obj_info(const t_obj* obj)
{
	while (obj)
	{
		if (obj->flag == plane || obj->flag == disk)
			ft_print_plane(obj->data);
		else if (obj->flag == sphere)
			ft_print_sphere(obj->data);
		else if (obj->flag == box)
			ft_print_box(obj->data);
		else if (obj->flag == cone)
			ft_print_cone(obj->data);
		else
			printf("ERROR PRINT INFO! UNEXPECTABLE FLAG!\nFLAG CODE = %d\n", obj->flag);
		obj = obj->next;
	}
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
