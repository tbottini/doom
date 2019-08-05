#include "doom_nukem.h"

t_camera		*camera_init(t_camera *camera, t_sdl *sdl, int fov)
{
	camera->fov = fov;
	camera->d_screen = (sdl->size.x / 2) / tan(camera->fov / 2.0 * PI180);
	//camera->fov_ver = atan2(camera->d_screen, sdl->size.y / 2);
	camera->fov_ver = atan2(sdl->size.y / 2, camera->d_screen) * 2;
	printf("sdl size %d %d %f %f\n", sdl->size.x, sdl->size.y, (double)camera->fov, camera->fov_ver);
	return (camera);
}