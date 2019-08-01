#include "rasterize.h"

//on recupere un mur (= surface)
//on determine la hauteur de la surface avec le secteur associe
//se qui nous permet de ne plus dependre de la structure secteur
void		surface_to_triangles(t_triangle *triangle1, t_triangle *triangle2, t_wall *wall, t_sector *sector_wall)
{

	triangle1->v0 = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = wall->pillar->p.y,
		.z = sector_wall->h_floor
	};
	triangle1->v1 = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = wall->next->p.y,
		.z = sector_wall->h_ceil
	};
	triangle1->v2 = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = wall->pillar->p.y,
		.z = sector_wall->h_ceil
	};
	triangle2->v1 = triangle1->v1;
	triangle2->v2 = triangle1->v0;
	triangle2->v0 = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = wall->next->p.y,
		.z = sector_wall->h_floor
	};
}

void		surface_to_quad(t_quad *quad, t_wall *surface, t_sector *sector_wall)
{
	(*quad)[0].v = (t_fvct3)
	{
		.x = surface->pillar->p.x,
		.y = surface->pillar->p.y,
		.z = sector_wall->h_floor
	};

	(*quad)[1].v = (t_fvct3)
	{
		.x = surface->next->p.x,
		.y = surface->next->p.y,
		.z = sector_wall->h_ceil
	};
	(*quad)[2].v = (t_fvct3)
	{
		.x = surface->pillar->p.x,
		.y = surface->pillar->p.y,
		.z = sector_wall->h_ceil
	};
	(*quad)[3].v = (t_fvct3)
	{
		.x = surface->next->p.x,
		.y = surface->next->p.y,
		.z = sector_wall->h_floor
	};
}

void	quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2)
{
	tri1->v0 = (*quad)[0].v;
	tri1->v1 = (*quad)[1].v;
	tri1->v2 = (*quad)[2].v;
	tri2->v0 = (*quad)[0].v;
	tri2->v1 = (*quad)[1].v;
	tri2->v2 = (*quad)[3].v;
}
