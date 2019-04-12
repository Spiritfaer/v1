#include "main.h"

int main(int argc, char ** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtDumpMemoryLeaks();
	//_CrtMemState tmp;
	//_CrtMemCheckpoint(&tmp);
	//_CrtMemDumpAllObjectsSince(&tmp);

	t_sdl		*sdl = NULL;
	t_scena		scena;
	int8_t		index_scena = 0;

	ft_memset(&scena, 0, sizeof(t_scena));


	sdl = ft_new_sdl();
	new_scena(argv[1], &scena);

	obj_info(scena.obj_list);



	ft_render(sdl, &scena);
	destroy_camera(&scena.camera_point);

	if (sdl)
	{
		ft_del_sdl(sdl);
		free(sdl);
	}	
	//printf("ok!\n");
	return (0);
}
