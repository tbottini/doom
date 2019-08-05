#include "rasterize.h"

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

void			quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	tri1->v[0].p = (*quad)[0].p;
	tri1->v[1].p = (*quad)[1].p;
	tri1->v[2].p = (*quad)[2].p;
	tri2->v[0].p = (*quad)[0].p;
	tri2->v[1].p = (*quad)[1].p;
	tri2->v[2].p = (*quad)[3].p;
}

void			quad_to_triangle_wall(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	quad_to_triangle(quad, tri1, tri2);
	tri1->v[0].texel = (*quad)[0].texel;
	tri1->v[1].texel = (*quad)[1].texel;
	tri1->v[2].texel = (*quad)[2].texel;
	tri2->v[0].texel = (*quad)[0].texel;
	tri2->v[1].texel = (*quad)[1].texel;
	tri2->v[2].texel = (*quad)[3].texel;
}
