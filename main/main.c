#include "doom_nukem.h"
#include "rasterize.h"
#include "debug.h"

void		frustum_floor_intersection_debug(double fov_ver, t_fvct2 pillar_pos, double floor_diff, t_fvct2 rot, t_fvct2 pos)
{
	t_camera	camera;
	t_fvct2		pillar_pos;
	t_stat		stat;
	t_fvct2		len_sector;

	camera.fov_ver = (fov_ver / 2) * TO_RADIAN;
	//position dans le ref de la cam
	pillar_pos = pillar_pos;
	//le secteur est 4u au dessus, 3u en dessous
	len_sector = (t_fvct2){0, floor_diff};
	stat.pos = (t_fvct3){pos.x, pos.y, 0};
	stat.rot = rot;

	frustum_floor_intersection(&pillar_pos, &camera, &len_sector, &stat);
}

int			main(int ac, char **av)
{
	//frustum_floor_intersection_debug();
	return (0);
}
