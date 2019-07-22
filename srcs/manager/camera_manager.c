#include "doom_nukem.h"

t_camera		*camera_init(t_camera *camera, t_sdl *sdl, int fov)
{
	camera->fov = fov;
	camera->d_screen = (sdl->size.x / 2) / tan(camera->fov / 2.0 * PI180);
	camera->fov_ver = atan2(camera->d_screen, sdl->size.y / 2);
	camera->fov_ver = sdl->size.y * (camera->fov / (double)sdl->size.x);
	camera->fov_ver *= PI180;
	return (camera);
}