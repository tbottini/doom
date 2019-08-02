#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "sector.h"
# include "doom_struct.h"

typedef struct			s_triangle
{
	t_fvct3				v0;
	t_fvct3				v1;
	t_fvct3				v2;
	t_vct2				c0;
	t_vct2				c1;
	t_vct2				c2;
	uint32_t			*textures;
}						t_triangle;

typedef	struct			s_verticle
{
	t_fvct3				v;
	t_vct2				texel;
}						t_verticle;

typedef t_verticle		t_quad[4];


void					render_surface_rasterize(t_arch *arch, t_wall *surface, t_sector *sector, t_player *player);
void					surface_to_triangles(t_triangle *triangle1, t_triangle *triangle2, t_wall *wall, t_sector *sector_wall);
void					world_to_camera(t_triangle *triangle, t_player *player);
void					camera_to_screen(t_triangle *triangle, t_camera *camera, t_sdl *sdl);
void					triangle_show_verticles(t_screen *screen, t_triangle *triangle);
void					surface_to_quad(t_quad *quad, t_wall *surface, t_sector *sector_wall);
void					quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2);
void					quad_set_referential(t_quad *quad, t_stat *ref);
void					clipping_z(t_fvct3 *behind, t_fvct3 *correct);

#endif