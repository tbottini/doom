#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "sector.h"
# include "screen.h"
# include "player.h"

typedef	struct			s_verticle
{
	t_fvct3				p;
	t_vct2				texel;
}						t_verticle;

typedef struct			s_triangle
{
	t_verticle			v[3];
	t_txtr				*texture;
}						t_triangle;

typedef t_verticle		t_quad[4];


void					render_surface_rasterize(t_camera *camera, t_sdl *sdl, t_wall *surface, t_sector *sector, t_player *player);
void					world_to_camera(t_triangle *triangle, t_player *player);
void					triangle_cam_to_screen(t_triangle *triangle, t_camera *camera, t_sdl *sdl);
void					triangle_show_verticles(t_screen *screen, t_triangle *triangle);
void					surface_to_quad(t_quad *quad, t_wall *surface, t_sector *sector_wall);
void					quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2);
void					quad_world_to_camera(t_quad *quad, t_stat *ref);
void					verticle_clipping_z(t_verticle *behind, t_verticle *correct);
void					surface_to_quad_wall(t_quad *quad, t_wall *surface, t_sector sector_wall);
void					quad_to_triangle_wall(t_quad *quad, t_triangle *tri1, t_triangle *tri2);
#endif