#include "vmth.h"

t_v3d		vec_3invert_dir(const t_v3d *dir)
{
	t_v3d inv_dir;

	inv_dir.x = -dir->x;
	inv_dir.y = -dir->y;
	inv_dir.z = -dir->z;
	return (inv_dir);
}
