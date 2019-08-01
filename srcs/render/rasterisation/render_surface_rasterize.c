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

//t_sdl
void			render_surface_rasterize(t_arch *arch, t_wall *surface, t_sector *sector, t_player *player, t_camera *cam)
{
	t_triangle	triangle_left;
	t_triangle	triangle_right;
	int			front_of_cam;

	surface_to_triangles(&triangle_right, &triangle_left, surface, sector);
	world_to_camera(&triangle_right, player);
	front_of_cam = verticle_position_cam(&triangle_right);
	b_point_debug(arch, *(t_fvct2*)&player->stat.pos, WHITE);
	b_point_debug(arch, (t_fvct2){triangle_right.v0.y, triangle_right.v0.x}, RED);
	b_point_debug(arch, (t_fvct2){triangle_right.v1.y, triangle_right.v1.x}, GREEN);
	b_point_debug(arch, (t_fvct2){triangle_right.v2.y, triangle_right.v2.x}, BLUE_SOFT);

	if (front_of_cam == 3)
	{
		if (debug == 5)
			print_triangle(&triangle_right);
		camera_to_screen(&triangle_right, cam, arch->sdl);
		triangles_show_verticles(arch, &triangle_right, arch->sdl);
	}
	world_to_camera(&triangle_left, player);
	front_of_cam = verticle_position_cam(&triangle_left);
	if (front_of_cam == 3)
	{
		if (debug == 5)
			print_triangle(&triangle_left);
		camera_to_screen(&triangle_left, cam, arch->sdl);
		triangles_show_verticles(arch, &triangle_left, arch->sdl);
	}
	b_point_debug(arch, (t_fvct2){triangle_left.v0.y, triangle_left.v0.x}, RED);
}
