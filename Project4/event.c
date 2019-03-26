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

	i = false;
	if (cur_key[SDL_SCANCODE_W] && (i = true))
	{
		camera->matrix[3][1] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_S] && (i = true))
	{
		camera->matrix[3][1] -= time->speed;
	}
	if (cur_key[SDL_SCANCODE_A] && (i = true))
	{
		camera->matrix[3][0] -= time->speed;
	}
	if (cur_key[SDL_SCANCODE_D] && (i = true))
	{
		camera->matrix[3][0] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_SPACE] && (i = true))
	{
		camera->matrix[3][2] += time->speed;
	}
	if (cur_key[SDL_SCANCODE_LCTRL] && (i = true))
	{
		camera->matrix[3][2] -= time->speed;
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
			return (true);
		}
	}
	else if (cur_key[SDL_SCANCODE_DOWN])
	{
		if (cam->fov > 20)
		{
			cam->fov -= 1;
			printf("\nfov = %3.1f\n", cam->fov);
			return (true);
		}
	}
	return (false);
}

void	event_guard(t_sdl *sdl, t_camera *camera, t_time *time)
{
	time_tick(time);
	SDL_PollEvent(&sdl->event);
	sdl->cur_key = SDL_GetKeyboardState(NULL);

	if (sdl->event.type == SDL_QUIT)
		sdl->loop = false;
	if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
		sdl->loop = false;
	camera->on = move_camera(sdl->cur_key, camera->cam, time);
	camera->on = move_fov(sdl->cur_key, camera, time);
	if (sdl->event.key.type == SDL_KEYDOWN)
		camera->on = true;
}
