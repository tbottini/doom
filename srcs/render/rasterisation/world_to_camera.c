#include "doom_nukem.h"

void			fvct3_sub(t_fvct3 *vector_sub, t_fvct3 *vector_sub2)
{
	vector_sub->x -= vector_sub2->x;
	vector_sub->y -= vector_sub2->y;
	vector_sub->z -= vector_sub2->z;

}

void			fvct3_rotation(t_fvct3 *point, t_fvct2 rot)
{
	t_fvct3		tmp;

	tmp = *point;
	point->x = tmp.x * cos(rot.y) + tmp.z * sin(rot.y);
	point->z = tmp.x * -sin(rot.y) + tmp.z * cos(rot.y);
	tmp = *point;
	point->y = tmp.y * cos(rot.x) - tmp.z * sin(rot.x);
	point->z = tmp.y * sin(rot.x) + tmp.z * cos(rot.x);
}

/*
**	on deplace les point selon la position et la rotation de la camera
*/
void			world_to_camera(t_triangle *triangle, t_player *player)
{
	fvct3_sub(&triangle->v0, &player->stat.pos);
	fvct3_sub(&triangle->v1, &player->stat.pos);
	fvct3_sub(&triangle->v2, &player->stat.pos);
	fvct3_rotation(&triangle->v0, player->stat.rot);
	fvct3_rotation(&triangle->v1, player->stat.rot);
	fvct3_rotation(&triangle->v2, player->stat.rot);
}