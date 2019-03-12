#include "main.h"

void	ft_print_pos(const t_v3d *pos)
{
	printf("x = %6.2f; y = %6.2f; z = %6.2f;\n", pos->x, pos->y, pos->z);
}
void	ft_print_color(const t_rgb* color)
{
	printf("Red = %4d; Green = %4d; Blue = %4d;\nINT COLOR = %9d;\n", color->r, color->g, color->b, color->color);
}

void	ft_print_plane(const void *data) {}
void	ft_print_sphere(const void *data)
{
	const t_sphere* temp;
	temp = data;
	printf("\n---SPHERE INFO---\n");
	ft_print_pos(&temp->centr);
	ft_print_color(&temp->color);
	printf("Radius = %6.2f;\n", temp->radius);
	printf("------------------\n");
}

void	ft_print_cube(const void *data) {}
void	ft_print_cone(const void *data) {}

void	obj_info(const t_obj* obj)
{
	if (obj->flag == plane)
		ft_print_plane(obj->data);
	else if (obj->flag == sphere)
		ft_print_sphere(obj->data);
	else if (obj->flag == cube)
		ft_print_cube(obj->data);
	else if (obj->flag == cone)
		ft_print_cone(obj->data);
	else
		printf("ERROR PRINT INFO! UNEXPECTABLE FLAG!\nFLAG CODE = %d\n", obj->flag);
}