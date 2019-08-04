#include "rasterize.h"

void			fvct3_sub(t_fvct3 *vector_sub, t_fvct3 *vector_sub2)
{
	vector_sub->x -= vector_sub2->x;
	vector_sub->y -= vector_sub2->y;
	vector_sub->z -= vector_sub2->z;
}

void			fvct3_rotation(t_fvct3 *point, t_fvct2 rot)
{
	t_fvct3		tmp;

	rot.x = (rot.x - 90) * (M_PI / 180);
	rot.y = -rot.y * (M_PI / 180);

	tmp = *point;
	point->x = tmp.x * cos(rot.y) + tmp.y * sin(rot.y);
	point->y = tmp.x * -sin(rot.y) + tmp.y * cos(rot.y);
	tmp = *point;
	point->z = tmp.z * cos(rot.x) - tmp.y * sin(rot.x);
	point->y = tmp.z * sin(rot.x) + tmp.y * cos(rot.x);
}

/*
**	on deplace les point selon la position et la rotation de la camera
*/
void			world_to_camera(t_triangle *triangle, t_player *player)
{
	fvct3_sub(&triangle->v[0].p, &player->stat.pos);
	fvct3_sub(&triangle->v[1].p, &player->stat.pos);
	fvct3_sub(&triangle->v[2].p, &player->stat.pos);
	fvct3_rotation(&triangle->v[0].p, player->stat.rot);
	fvct3_rotation(&triangle->v[1].p, player->stat.rot);
	fvct3_rotation(&triangle->v[2].p, player->stat.rot);
}

/*
**	on change le referentiel d'un quad
**	les coordonnes du quad seront en fonction d'un stat, rotation position
*/
void			quad_world_to_camera(t_quad *quad, t_stat *ref)
{
	fvct3_sub(&(*quad)[0].p, &ref->pos);
	fvct3_sub(&(*quad)[1].p, &ref->pos);
	fvct3_sub(&(*quad)[2].p, &ref->pos);
	fvct3_sub(&(*quad)[3].p, &ref->pos);
	fvct3_rotation(&(*quad)[0].p, ref->rot);
	fvct3_rotation(&(*quad)[1].p, ref->rot);
	fvct3_rotation(&(*quad)[2].p, ref->rot);
	fvct3_rotation(&(*quad)[3].p, ref->rot);
}