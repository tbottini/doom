#include "rasterize.h"
#include "color.h"

/*
**	on projete les point dans une proportion de l'ecran
*/
void		triangle_cam_to_screen(t_triangle *triangle, t_camera *camera, t_sdl *sdl)
{
	t_fvct2	fov_tan;

	triangle->v[0].p.x /= triangle->v[0].p.y;
	triangle->v[0].p.z /= triangle->v[0].p.y;
	triangle->v[1].p.x /= triangle->v[1].p.y;
	triangle->v[1].p.z /= triangle->v[1].p.y;
	triangle->v[2].p.x /= triangle->v[2].p.y;
	triangle->v[2].p.z /= triangle->v[2].p.y;

	fov_tan.x = tan((camera->fov / 2) * (M_PI / 180));
	fov_tan.y = camera->fov_ver / 2;

	triangle->v[0].p.x = sdl->size.x / 2 - (triangle->v[0].p.x / fov_tan.x) * sdl->size.x;
	triangle->v[0].p.z = sdl->size.y / 2 - (triangle->v[0].p.z / fov_tan.y) * sdl->size.y;
	triangle->v[1].p.x = sdl->size.x / 2 - (triangle->v[1].p.x / fov_tan.x) * sdl->size.x;
	triangle->v[1].p.z = sdl->size.y / 2 - (triangle->v[1].p.z / fov_tan.y) * sdl->size.y;
	triangle->v[2].p.x = sdl->size.x / 2 - (triangle->v[2].p.x / fov_tan.x) * sdl->size.x;
	triangle->v[2].p.z = sdl->size.y / 2 - (triangle->v[2].p.z / fov_tan.y) * sdl->size.y;
}

/*
**	on affiche les arretes du triangle
*/
void		triangle_show_verticles(t_screen *screen, t_triangle *triangle)
{
	trait(screen, (t_vct2){triangle->v[0].p.x, triangle->v[0].p.z}, (t_vct2){triangle->v[1].p.x, triangle->v[1].p.z}, BLUE);
	trait(screen, (t_vct2){triangle->v[1].p.x, triangle->v[1].p.z}, (t_vct2){triangle->v[2].p.x, triangle->v[2].p.z}, BLUE);
	trait(screen, (t_vct2){triangle->v[2].p.x, triangle->v[2].p.z}, (t_vct2){triangle->v[0].p.x, triangle->v[0].p.z}, BLUE);
}
