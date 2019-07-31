#include "doom_nukem.h"

int				verticle_position_cam(t_triangle *triangle)
{
	return ((triangle->v0.z > 1) + (triangle->v1.z > 1) + (triangle->v2.z > 1));
}

void			render_surface_rasterize(t_wall *surface, t_sector *sector, t_player *player, t_camera *cam)
{
	t_triangle	triangle_left;
	t_triangle	triangle_right;
	int			front_of_cam;

	surface_to_triangle(&triangle_right, &triangle_left, surface, wall, sector);
	world_to_camera(&triangle_right, player);
	front_of_cam = verticle_position_cam(&triangle_left);
	if (front_of_cam == 0)
		printf("pas de rendu de triangle verticles behind cam\n");
	else if (front_of_cam == 1)
		printf("deux intersection et formation d'un triangle\n");
	else if (front_of_cam == 2)
		printf("deux intersection et formation de deux triangles\n");
	else
		printf("rendu normal, le triangle est en face de la camera\n");
}
