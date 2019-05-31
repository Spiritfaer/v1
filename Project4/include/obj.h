#ifndef OBJ_H
#define OBJ_H

#include "vmth.h"
#include "color.h"

enum e_type_flag { plane, sphere, box, cone, disk,  };

typedef struct		s_sphere
{
	t_v3d			world_centr;
	t_v3d			cam_centr;
	t_rgb			color;
	double_t		radius;
	double_t		rad2;
	double_t		reflection;
}					t_sphere;

typedef struct		s_plane
{
	t_v3d			world_normal;
	t_v3d			world_centr;
	t_v3d			cam_normal;
	t_v3d			cam_centr;
	t_rgb			color;
	double_t		size;
	double_t		s2;
	double_t		reflection;
}					t_plane;

typedef struct		s_box
{
	t_v3d			min;
	t_v3d			max;
	t_v3d			cam_min;
	t_v3d			cam_max;
	t_v3d			centr;
	double_t		size;
	t_rgb			color;
	double_t		reflection;
}					t_box;

typedef struct		s_cone
{
	t_v3d			cam_centr;
	t_v3d			cam_normal; //axe
	t_v3d			world_centr;
	t_v3d			world_normal; //axe
	t_rgb			color;
	double_t		radius;
	double_t		reflection;

	double		angle;
	double		size;
	double      hauteur;
	double		specular;

}					t_cone;

typedef	struct		s_light
{
	t_v3d			pos;
	t_v3d			cam_pos;
	t_rgb			color;
	t_v3d			dir_to_hit;
	t_rgb			light_color;
	double_t		power_light;
	t_v3d			intensity_light;
	double_t		r2;
	t_v3d			invdir;
	t_matrix		*transform;
	struct s_light	*next;
}					t_light;

#endif