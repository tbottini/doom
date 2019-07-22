#include "doom_nukem.h"


int				render_shape(t_arch *arch, t_shap shape)
{
	return (0);
}


/*

*/

/*
**	renvoie la position au sol qui rejoint le bas du pillier
**	up : la position en z du haut du pillier par rapport au joueur (en u)
**	down : idem que up mais pour le bas (en u)
**	surface : la taille du pillier sur l'ecran
*/
t_fvct2			get_floor_pos(t_arch *arch, t_fvct2 len, t_fvct2 surface, t_fvct2 *pillar)
{
	double		px_to_u;
	t_fvct2		floor_pos;

	px_to_u = (len.x - len.y) / (surface.y / surface.x);
	//on recupere l'intersection en profondeur
	floor_pos.x = len.x / arch->cam->fov_ver;
	floor_pos.x = floor_pos.x * px_to_u;
	//on recupere decal
	floor_pos.y = (pillar->y / pillar->x) * floor_pos.x;
	return (floor_pos);
}

t_shap			shape_def(t_fvct2 up_left, t_fvct2 up_right, t_fvct2 bot_left, t_fvct2 bot_right)
{
	t_shap		shape;

	shape.ul = up_left;
	shape.ur = up_right;
	shape.bl = bot_left;
	shape.br = bot_right;
	return (shape);
}

int				render_floor(t_arch *arch, t_shap shape)
{
	t_shap		floor_s;

	render_shape(arch, shape);
	//start render

	return (1);
}
