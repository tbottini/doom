#include "rasterize.h"

//on recupere un mur (= surface)
//on determine la hauteur de la surface avec le secteur associe
//se qui nous permet de ne plus dependre de la structure secteur
void		surface_to_triangles(t_triangle *triangle1, t_triangle *triangle2, t_wall *wall, t_sector *sector_wall)
{

	triangle1->v[0].p = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = wall->pillar->p.y,
		.z = sector_wall->h_floor
	};
	triangle1->v[1].p = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = wall->next->p.y,
		.z = sector_wall->h_ceil
	};
	triangle1->v[2].p = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = wall->pillar->p.y,
		.z = sector_wall->h_ceil
	};
	triangle2->v[1].p = triangle1->v[1].p;
	triangle2->v[2].p = triangle1->v[0].p;
	triangle2->v[0].p = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = wall->next->p.y,
		.z = sector_wall->h_floor
	};
}

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

void	quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	tri1->v[0].p = (*quad)[0].p;
	tri1->v[1].p = (*quad)[1].p;
	tri1->v[2].p = (*quad)[2].p;
	tri2->v[0].p = (*quad)[0].p;
	tri2->v[1].p = (*quad)[1].p;
	tri2->v[2].p = (*quad)[3].p;
}
