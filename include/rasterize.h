#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "sector.h"
# include "doom_struct.h"

typedef struct		s_triangle
{
	t_fvct3			v0;
	t_fvct3			v1;
	t_fvct3			v2;
	t_vct2			c0;
	t_vct2			c1;
	t_vct2			c2;
	uint32_t		*textures;
}					t_triangle;

void			render_surface_rasterize(t_wall *surface, t_player *player, t_camera *cam);
void			surface_to_triangles(t_triangle *triangle1, t_triangle *triangle2, t_wall *wall, t_sector *sector_wall);
void			world_to_camera(t_triangle *triangle, t_player *player);

#endif