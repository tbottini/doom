#include "doom_nukem.h"

void			print_triangle(t_triangle *triangle)
{
	printf("triangle");
	printf("v0: %f %f %f\n", triangle->v0.x, triangle->v0.y, triangle->v0.z);
	printf("v1: %f %f %f\n", triangle->v1.x, triangle->v1.y, triangle->v1.z);
	printf("v2: %f %f %f\n", triangle->v2.x, triangle->v2.y, triangle->v2.z);
}

int				verticle_position_cam(t_triangle *triangle)
{
	return ((triangle->v0.y > 1) + (triangle->v1.y > 1) + (triangle->v2.y > 1));
}


void			render_triangle(t_arch *arch, t_triangle *tri)
{
	int			vert_in_cam;

	vert_in_cam = verticle_position_cam(tri);
	if (vert_in_cam == 3)
	{
		camera_to_screen(tri, arch->cam, arch->sdl);
		triangle_show_verticles(arch, tri);
	}
}

//t_sdl
void			render_surface_rasterize(t_arch *arch, t_wall *surface, t_sector *sector, t_player *player)
{
	t_verticle		quad[4];
	t_triangle	triangles[2];

	surface_to_quad(&quad, surface, sector);
	quad_set_referential(&quad, &player->stat);
	quad_to_triangle(&quad, &triangles[0], &triangles[1]);
	render_triangle(arch, &triangles[0]);
	render_triangle(arch, &triangles[1]);
}
