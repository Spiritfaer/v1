#include "vmth.h"

t_v3d	mult_vect_matrix_3_3(t_v3d world_centr, double_t **invert_matrix)
{
	t_v3d point = { 0, 0, 0 };

	point.x = world_centr.x * invert_matrix[0][0] + world_centr.y * invert_matrix[1][0] + world_centr.z * invert_matrix[2][0];
	point.y = world_centr.x * invert_matrix[0][1] + world_centr.y * invert_matrix[1][1] + world_centr.z * invert_matrix[2][1];
	point.z = world_centr.x * invert_matrix[0][2] + world_centr.y * invert_matrix[1][2] + world_centr.z * invert_matrix[2][2];

	return (point);
}

t_v3d	mult_vect_matrix_4_4(t_v3d world_centr, double_t **invert_matrix)
{
	double_t w;
	t_v3d point = { 0, 0, 0 };

	point.x = world_centr.x * invert_matrix[0][0] + world_centr.y * invert_matrix[1][0] + world_centr.z * invert_matrix[2][0] + invert_matrix[3][0];
	point.y = world_centr.x * invert_matrix[0][1] + world_centr.y * invert_matrix[1][1] + world_centr.z * invert_matrix[2][1] + invert_matrix[3][1];
	point.z = world_centr.x * invert_matrix[0][2] + world_centr.y * invert_matrix[1][2] + world_centr.z * invert_matrix[2][2] + invert_matrix[3][2];
	w = world_centr.x * invert_matrix[0][3] + world_centr.y * invert_matrix[1][3] + world_centr.z * invert_matrix[2][3] + invert_matrix[3][3];
	if (w != 0 && w != 1)
	{
		point.x = (point.x + 1) / w;
		point.y = (point.y + 1) / w;
		point.z = (point.z + 1) / w;
	}
	return (point);
}
