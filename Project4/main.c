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

	char *scena_file_0 = "C:\\Users\\User\\source\\repos\\Project4\\Project4\\figure_v_1.txt";
	char *scena_file_1 = "C:\\Users\\User\\source\\repos\\Project4\\Project4\\scena_1.txt";

	ft_memset(&scena, 0, sizeof(t_scena));
	sdl = ft_new_sdl();
	//new_scena(argv[1], &scena);
	//new_scena(scena_file_0, &scena);
	new_scena(scena_file_1, &scena);
	obj_info(scena.obj_list);
	ft_render(sdl, &scena);
	destroy_camera(&scena.camera_point);
	if (sdl)
	{
		ft_del_sdl(sdl);
		free(sdl);
	}	

	return (0);
}
