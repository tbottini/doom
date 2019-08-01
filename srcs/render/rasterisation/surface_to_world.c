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
