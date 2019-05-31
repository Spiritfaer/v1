#ifndef STRUCT_H
#define STRUCT_H

#include "vmth.h"
#include "color.h"

#define _INF (DBL_MAX*2)

//enum e_type_flag	{plane, sphere, box, cone, disk};

typedef struct		s_aabb_ray
{
	t_v3d			invdir;
	int8_t			flag[3];
}					t_aabb_ray;

typedef struct		s_ray
{
	t_v3d			orig;
	t_v3d			dir;
	int16_t			type;
}					t_ray;

typedef struct 		s_obj
{
	void			*data;
	int8_t(*intersect)(t_ray *ray, const void *data, double_t *t);
	t_rgb(*get_color)(const void* data);
	t_v3d(*get_center)(const void* data);
	t_v3d(*get_n_hit)(const t_v3d *point_hit, const struct s_obj *obj);
	double_t(*get_reflection)(const void* data);
	void(*to_camera)(const t_matrix *camera, void *src);
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
	t_rgb			bg_color;
}					t_camera;

typedef struct		s_scena
{
	t_obj			*obj_list;
	t_light			*light_list;
	t_camera		*camera_point;
	t_list			*head_list;
}					t_scena;

typedef struct		s_sdl
{
	int8_t			init_flag;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*canvas;
	SDL_Event		event;
	const uint8_t	*cur_key;
	char			*win_name;
	t_v2i			screen_size;
	double_t		iar;	// image Aspect // Ratio DONT WORK!!!
	int8_t			loop;
}					t_sdl;

typedef struct		s_hit
{
	t_v3d			point_hit;
	t_v3d			norml_hit;
	t_rgb			color_hit;
	t_obj			*hit_obj;
	double_t		shadow;
	double_t		tNear;
	double_t		t;
}					t_hit;

#endif