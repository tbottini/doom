#include "doom_nukem.h"

/*
**	renvoie l'index de la texture associee au pixel de l'ecran
**	l'affine du mur est le decal(y) selon depth(x)
**	pblm on peut avoir un mur face au joueur formant
**	une affine constante verticalement
*/
uint32_t		texture_interpolation2D(t_designer *arch)
{
	t_affine	px_affine;
	t_affine	wall_affine;
	t_fvct2		inter;
	double		percent;

	px_affine.a = ((arch->sdl->size.x / 2) - arch->px.x) / arch->cam->d_screen;
	px_affine.b = 0;
	if ((int)((arch->depth.y - arch->depth.x) * 100) == 0)
	{
		inter.x = arch->depth.y;
		inter.y = px_affine.a * inter.x;
		percent = (inter.y - arch->decal.x) / (arch->decal.y - arch->decal.x);
	}
	else
	{
		wall_affine.a = (arch->decal.y - arch->decal.x) / (arch->depth.y - arch->depth.x);
		wall_affine.b = arch->decal.x - wall_affine.a * arch->depth.x;
		inter = interpolation_linear(wall_affine, px_affine);
		percent = (inter.x - arch->depth.x) / (arch->depth.y - arch->depth.x);
	}
	percent = percent * (arch->shift_txtr.y -  arch->shift_txtr.x) + arch->shift_txtr.x;
	return (percent * arch->wall->txtr.w);
}
