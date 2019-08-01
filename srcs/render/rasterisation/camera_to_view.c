#include "rasterize.h"
#include "debug.h"

/*
**	on projete les point dans une proportion de l'ecran
*/
void		camera_to_screen(t_triangle *triangle, t_camera *camera, t_sdl *sdl)
{
	t_fvct2	fov_tan;

	triangle->v0.x /= triangle->v0.y;
	triangle->v0.z /= triangle->v0.y;
	triangle->v1.x /= triangle->v1.y;
	triangle->v1.z /= triangle->v1.y;
	triangle->v2.x /= triangle->v2.y;
	triangle->v2.z /= triangle->v2.y;

	fov_tan.x = tan((camera->fov / 2) * (M_PI / 180));
	fov_tan.y = camera->fov_ver / 2;

	triangle->v0.x = sdl->size.x / 2 - (triangle->v0.x / fov_tan.x) * sdl->size.x;
	triangle->v0.z = sdl->size.y / 2 - (triangle->v0.z / fov_tan.y) * sdl->size.y;
	triangle->v1.x = sdl->size.x / 2 - (triangle->v1.x / fov_tan.x) * sdl->size.x;
	triangle->v1.z = sdl->size.y / 2 - (triangle->v1.z / fov_tan.y) * sdl->size.y;
	triangle->v2.x = sdl->size.x / 2 - (triangle->v2.x / fov_tan.x) * sdl->size.x;
	triangle->v2.z = sdl->size.y / 2 - (triangle->v2.z / fov_tan.y) * sdl->size.y;
}

void		triangles_show_verticles(t_arch *arch, t_triangle *triangle, t_sdl *sdl)
{
	//sdl->screen[(int)(triangle->v0.x + triangle->v0.z * sdl->size.x)] = 0xffffffff;
	//sdl->screen[(int)(triangle->v1.x + triangle->v1.z * sdl->size.x)] = 0xffffffff;
	//sdl->screen[(int)(triangle->v2.x + triangle->v2.z * sdl->size.x)] = 0xffffffff;
	trait(arch, (t_vct2){triangle->v0.x, triangle->v0.z}, (t_vct2){triangle->v1.x, triangle->v1.z}, BLUE);
	trait(arch, (t_vct2){triangle->v1.x, triangle->v1.z}, (t_vct2){triangle->v2.x, triangle->v2.z}, BLUE);
	trait(arch, (t_vct2){triangle->v2.x, triangle->v2.z}, (t_vct2){triangle->v0.x, triangle->v0.z}, BLUE);
}
