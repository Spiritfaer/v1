#ifndef STRUCT_H
#define STRUCT_H

#include "SDL.h"
#include "vmth.h"

enum e_type_flag	{plane, sphere, cube, cone};

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
}					t_sphere;

typedef struct 		s_obj
{
	void			*data;
	//int8_t(*intersect)(const void* data, const t_v3d ray_start_point, 
	//					const t_v3d ray, t_v3d* const intersect_point);
	int8_t(*intersect)(const t_v2i i, const t_sphere* my_sphere);
	//t_rgb(*get_color)(const void* data, const t_v3d* intersect_point);
	t_rgb(*get_color)(const void* data);
	uint8_t			flag;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_sdl
{
	int8_t			init_flag;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	const uint8_t	*cur_key;
	char			*win_name;
	t_v2i			screen_size;
	int8_t			loop;
}					t_sdl;

typedef struct		s_time
{
	double_t		old_time;
	double_t		time;
	double_t		frame_time;
	double_t		speed;
}					t_time;

#endif