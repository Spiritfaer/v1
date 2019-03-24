#include "main.h"

void	time_tick(t_time *t)
{
	t->old_time = t->time;
	t->time = SDL_GetTicks();
	t->frame_time = (t->time - t->old_time) / 10000.0;
	t->speed = t->frame_time * 30.0;
}
void	move_camera(uint8_t *cur_key, t_matrix *camera, t_time *time)
{
	if (cur_key[SDL_SCANCODE_W])
	{
		camera->matrix[3][1] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_S])
	{
		camera->matrix[3][1] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_A])
	{
		camera->matrix[3][0] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_D])
	{
		camera->matrix[3][0] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_SPACE])
	{
		camera->matrix[3][2] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
	if (cur_key[SDL_SCANCODE_LCTRL])
	{
		camera->matrix[3][2] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
	}
}

void	event_guard(t_sdl *sdl, t_camera *camera, t_time *time)
{
	time_tick(&time);
	SDL_PollEvent(&sdl->event);
	sdl->cur_key = SDL_GetKeyboardState(NULL);

	if (sdl->event.type == SDL_QUIT)
		sdl->loop = 0;
	if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
		sdl->loop = 0;
	move_camera(sdl->cur_key, camera->cam, &time);
}
