#include "rasterize.h"

//on recupere un mur (= surface)
//on determine la hauteur de la surface avec le secteur associe
//se qui nous permet de ne plus dependre de la structure secteur
void		surface_to_triangles(t_triangle *triangle1, t_triangle *triangle2, t_wall *wall, t_sector *sector_wall)
{

	triangle1->v0 = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = sector_wall->h_floor,
		.z = wall->pillar->p.y
	};
	triangle1->v1 = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = sector_wall->h_ceil,
		.z = wall->next->p.y
	};
	triangle1->v2 = (t_fvct3)
	{
		.x = wall->pillar->p.x,
		.y = sector_wall->h_ceil,
		.z = wall->pillar->p.y
	};
	triangle2->v1 = triangle1->v1;
	triangle2->v2 = triangle2->v0;
	triangle2->v0 = (t_fvct3)
	{
		.x = wall->next->p.x,
		.y = sector_wall->h_floor,
		.z = wall->next->p.y
	};
}
