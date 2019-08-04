#include "rasterize.h"

/*
**	quad[0] bas gauche (pillar/sol)
**	quad[1] haut droite (next/plafond)
**	quad[2] haut gauche (pillar/plafond)
**	quad[3] bas droite (next/sol)
*/
void		surface_to_quad(t_quad *quad, t_wall *surface, t_sector *sector_wall)
{
	(*quad)[0].p = (t_fvct3)
	{
		.x = surface->pillar->p.x,
		.y = surface->pillar->p.y,
		.z = sector_wall->h_floor
	};
	(*quad)[1].p = (t_fvct3)
	{
		.x = surface->next->p.x,
		.y = surface->next->p.y,
		.z = sector_wall->h_ceil
	};
	(*quad)[2].p = (t_fvct3)
	{
		.x = surface->pillar->p.x,
		.y = surface->pillar->p.y,
		.z = sector_wall->h_ceil
	};
	(*quad)[3].p = (t_fvct3)
	{
		.x = surface->next->p.x,
		.y = surface->next->p.y,
		.z = sector_wall->h_floor
	};
}

void		surface_to_quad_wall(t_quad *quad, t_wall *surface, t_sector sector_wall)
{
	surface_to_quad(quad, surface, sector_wall);
	(*quad)[0].texel = (t_vct2){0, 0};
	(*quad)[1].texel = (t_vct2){surface->txtr.w, surface->txtr.h};
	(*quad)[2].texel = (t_vct2){0, surface->txtr.h};
	(*quad)[3].texel = (t_vct2){surface->txtr.w, 0};
}

void	quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	tri1->v[0].p = (*quad)[0].p;
	tri1->v[1].p = (*quad)[1].p;
	tri1->v[2].p = (*quad)[2].p;
	tri2->v[0].p = (*quad)[0].p;
	tri2->v[1].p = (*quad)[1].p;
	tri2->v[2].p = (*quad)[3].p;
}

void	quad_to_triangle_wall(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	quad_to_triangle(quad, tri1, tri2);
	tri1->v[0].texel = (*quad)[0].texel;
	tri1->v[1].texel = (*quad)[1].texel;
	tri1->v[2].texel = (*quad)[2].texel;
	tri2->v[0].texel = (*quad)[0].texel;
	tri2->v[1].texel = (*quad)[1].texel;
	tri2->v[2].texel = (*quad)[3].texel;
}

//quad convert triangle