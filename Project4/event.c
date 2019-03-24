#include "main.h"

void	time_tick(t_time *t)
{
	t->old_time = t->time;
	t->time = SDL_GetTicks();
	t->frame_time = (t->time - t->old_time) / 10000.0;
	t->speed = t->frame_time * 30.0;
}
uint8_t	move_camera(const uint8_t *cur_key, t_matrix *camera, t_time *time)
{
	uint8_t i;

	i = 0;
	if (cur_key[SDL_SCANCODE_W])
	{
		camera->matrix[3][1] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	if (cur_key[SDL_SCANCODE_S])
	{
		camera->matrix[3][1] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	if (cur_key[SDL_SCANCODE_A])
	{
		camera->matrix[3][0] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	if (cur_key[SDL_SCANCODE_D])
	{
		camera->matrix[3][0] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	if (cur_key[SDL_SCANCODE_SPACE])
	{
		camera->matrix[3][2] += time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	if (cur_key[SDL_SCANCODE_LCTRL])
	{
		camera->matrix[3][2] -= time->speed;
		//print_matrix(camera->matrix, camera->size);
		//print_matrix(camera->invert_matrix, camera->size);
		i = 1;
	}
	return (i);
}

uint8_t	move_fov(const uint8_t *cur_key, t_camera *cam, t_time *time)
{
	if (cur_key[SDL_SCANCODE_UP])
	{
		if (cam->fov < 150)
		{
			cam->fov += 1;
			printf("\nfov = %3.1f\n", cam->fov);
			return (1);
		}
	}
	else if (cur_key[SDL_SCANCODE_DOWN])
	{
		if (cam->fov > 20)
		{
			cam->fov -= 1;
			printf("\nfov = %3.1f\n", cam->fov);
			return (1);
		}
	}
	return (0);
}

void	event_guard(t_sdl *sdl, t_camera *camera, t_time *time)
{
	time_tick(time);
	SDL_PollEvent(&sdl->event);
	sdl->cur_key = SDL_GetKeyboardState(NULL);

	if (sdl->event.type == SDL_QUIT)
		sdl->loop = 0;
	if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
		sdl->loop = 0;
	camera->on = move_camera(sdl->cur_key, camera->cam, time);
	camera->on = move_fov(sdl->cur_key, camera, time);
	if (sdl->event.key.type == SDL_KEYDOWN)
		camera->on = 1;
}
