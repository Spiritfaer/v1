#ifndef STRUCT_H
#define STRUCT_H

#include "vmth.h"

#define _INF (DBL_MAX*2)

enum e_type_flag	{plane, sphere, box, cone, disk};

typedef struct		s_rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint32_t		color;
}					t_rgb;

typedef struct		s_sphere
{
	t_v3d			world_centr;
	t_v3d			cam_centr;
	t_rgb			color;
	double_t		radius;
	double_t		rad2;
	t_v3d			albedo;
}					t_sphere;

typedef struct		s_plane
{
	t_v3d			world_normal;
	t_v3d			world_centr;
	t_v3d			cam_normal;
	t_v3d			cam_centr;
	t_v3d			albedo;
	t_rgb			color;
	double_t		size;
	double_t		s2;
}					t_plane;

typedef struct		s_aabb_ray
{
	t_v3d			invdir;
	int8_t			flag[3];
}					t_aabb_ray;

typedef struct		s_box
{
	t_v3d			min;
	t_v3d			max;
	t_v3d			cam_min;
	t_v3d			cam_max;
	//t_v3d			tmin;
	//t_v3d			tmax;
	//t_v3d			bounds[2];
	t_v3d			centr;
	double_t		size;
	t_rgb			color;
	t_v3d			albedo;
}					t_box;

typedef	struct		s_light
{
	t_v3d			pos;
	t_v3d			cam_pos;
	t_rgb			color;
	double_t		light_color;
	double_t		intensity;
	t_v3d			dir;
	t_v3d			invdir;
	t_matrix		*transform;
	struct s_light	*next;
}					t_light;

typedef struct 		s_obj
{
	void			*data;
	int8_t(*intersect)(t_v3d *orig, t_v3d *dir, const void *data, double_t *t);
	//t_rgb(*get_color)(const void* data, const t_v3d* intersect_point);
	t_rgb(*get_color)(const void* data);
	t_v3d(*get_center)(const void* data);
	t_v3d(*get_albedo)(const void* data);
	t_v3d(*get_n_hit)(const t_v3d *point_hit, const struct s_obj *obj);
	uint8_t			flag;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_time
{
	double_t		old_time;
	double_t		time;
	double_t		frame_time;
	double_t		speed;
}					t_time;

typedef struct		s_camera
{
	t_matrix		*cam;
	t_v3i			oryg;
	t_v3d			dir;
	double_t		t;
	double_t		max_t;
	double_t		min_t;
	double_t		fov;
	double_t		scale;
	uint8_t			on;
}					t_camera;

typedef struct		s_sdl
{
	int8_t			init_flag;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	const uint8_t	*cur_key;
	char			*win_name;
	t_v2i			screen_size;
	double_t		iar;	//image Aspect Ratio  
	int8_t			loop;
}					t_sdl;


#endif