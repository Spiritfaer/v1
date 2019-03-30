#include "main.h"


int main(int argc, char ** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtDumpMemoryLeaks();

	t_sdl		*sdl = NULL;
	t_obj		*obj = NULL;
	t_light		*suns = NULL;
	t_v3d		centr;
	t_v3d		centr2;
	t_rgb		color;
	double_t	radius;
	int32_t		q = 3;
	int8_t		scena = 1;
	sdl = ft_new_sdl();
	
	ft_temp_fill(&centr, &color, &radius, sdl->screen_size);
	obj = ft_new_sphere(centr, color, radius);

	if (scena == 0)
	{
		centr = vec_3d(-2.0, 3.0, -1.5);
		set_color(&color, 33, 66, 30);
		radius = 1.5 * q;
		push_back_obj(ft_new_sphere(centr, color, radius), obj);

		centr = vec_3d(10.0, 7.0, 1.0);
		set_color(&color, 83, 55, 122);
		radius = 0.7 * q;
		push_back_obj(ft_new_sphere(centr, color, radius), obj);

		centr = vec_3d(7.0, 7.0, -0.5);
		set_color(&color, 255, 255, 255);
		radius = 1.3 * q;
		push_back_obj(ft_new_sphere(centr, color, radius), obj);

		centr = vec_3d(0.0, -5.5, 0.0);
		set_color(&color, 200, 200, 25);
		radius = 5 * q;
		push_back_obj(ft_new_plane(centr, color, radius, disk), obj);

		centr = (t_v3d) { 15, -1, 0 };
		//centr = (t_v3d) { 1, 1, 1 };
		//centr2 = (t_v3d) { -1, -1, -1 };
		set_color(&color, 35, 75, 150);
		push_back_obj(ft_new_box(&centr, NULL, color, (double_t)2.0), obj);
	}
	else
	{
		centr = vec_3d(0.0, -5.5, 0.0);
		set_color(&color, 200, 200, 25);
		radius = 5 * q;
		push_back_obj(ft_new_plane(centr, color, radius, disk), obj);

		centr = vec_3d(0.0, 25.0, -1.0);
		set_color(&color, 255, 255, 255);
		push_back_light(new_light(&centr, &color, (double_t)100.0), suns);
	}


	obj_info(obj);

	_CrtMemState tmp;
	_CrtMemCheckpoint(&tmp);

	ft_render(sdl, obj, suns);

	if (obj)
		ft_del_sphere(&obj);

	if (sdl)
	{
		ft_del_sdl(sdl);
		free(sdl);
	}
	_CrtMemDumpAllObjectsSince(&tmp);
	printf("ok!\n");
	return (0);
}
