#include "render.h"
#include "debug.h"
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
	t_fvct2		inte;

	//len.x - len.y car len.y est negatif
	px_to_u = (len.x - len.y) / (surface.y - surface.x) / 2;


	//intersection entre le frustum et le bas du pillier
	//convertion du point d'intersection en distance (u) en utilisant le rapport du pillier (surface / hauteur)
	//	la distance = profondeur - intersection.x
	//	distance = distance * px_to_u
	//recuperation de y


	//on recupere l'intersection en profondeur
	floor_pos.x = ((arch->sdl->size.y / 2) - surface.y) / tan(-arch->cam->fov_ver / 2);
	floor_pos.x = arch->cam->d_screen - floor_pos.x;
	floor_pos.x = floor_pos.x * px_to_u;
	floor_pos.x = pillar->x - floor_pos.x;
	//on recupere decal
	floor_pos.y = (pillar->y / pillar->x) * floor_pos.x;


	if (arch->depth_portal > 0)
	{
		inte = inter(arch->pillar, arch->next, arch->portal.pillar, arch->portal.next);
		b_point_debug(inte, RED);
		if (inte.x > floor_pos.x)
			floor_pos = inte;
	}

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

