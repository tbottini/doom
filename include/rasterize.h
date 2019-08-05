#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "sector.h"
# include "screen.h"
# include "player.h"
# include "calcul.h"

typedef	struct			s_verticle
{
	t_fvct3				p;
	t_vct2				texel;
}						t_verticle;

typedef struct			s_triangle
{
	t_verticle			v[3];
	t_txtr				*texture;
	double				area;
}						t_triangle;

typedef t_verticle		t_quad[4];

typedef struct 		s_cursor
{
	t_vct2			cursor;
	t_vct2			line;		//les limite de la ligne
	t_fvct2			buff_cursor; //precision du vecteur de cursor
	double			long_curve;
	double			up_curve; //augmentation du nombre de pixel jusqu a la mid limit
	double			down_curve; //augmentation du pixel jusqu a la derniere limite
	int				mid_limit; //augmentation du pixel jusqu a
	int				down_limit;
	bool			mid_on_left; //le verticles du millier est t-il dans le millieu ou non
}					t_cursor;


void					render_surface_rasterize(t_camera *camera, t_sdl *sdl, t_wall *surface, t_sector *sector, t_player *player);
void					world_to_camera(t_triangle *triangle, t_player *player);
void					triangle_cam_to_screen(t_triangle *triangle, t_camera *camera, t_sdl *sdl);
void					triangle_show_verticles(t_screen *screen, t_triangle *triangle);
void					surface_to_quad(t_quad *quad, t_wall *surface, t_sector *sector_wall);
void					quad_to_triangle(t_quad *quad, t_triangle *tri1, t_triangle *tri2);
void					quad_world_to_camera(t_quad *quad, t_stat *ref);
void					verticle_clipping_z(t_verticle *behind, t_verticle *correct);
void					surface_to_quad_wall(t_quad *quad, t_wall *surface, t_sector *sector_wall);
void					quad_to_triangle_wall(t_quad *quad, t_triangle *tri1, t_triangle *tri2);
void					texture_mapping(t_sdl *sdl, t_triangle *triangle);
/*
**	cursor
*/

#endif