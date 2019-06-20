#include "doom_nukem.h"

//on recupere le pixel on determine une affine
//on recupere les point projete sur l'ecran
//				leurs pourcentage, position
//on en determine aussi une affine
//on fait une interpolation lineaire des deux
//on recupere le point d'intersection
//on defini un pourcentage dans le segment du mur
//on recupere la position u (largeur) dans la texture
//elle sera renvoyer


/*
**	renvoie l'index de la texture associe au pixel de l'ecran
*/
int				texture_interpolation2D(t_designer *arch)
{
	t_affine	px_affine;
	t_affine	wall_affine;
	t_fvct2		inter;
	double		percent;

	//on determine les affine du mur est du
	px_affine = affine_def(((arch->sdl.size.x / 2) - arch->px.x) / arch->sdl.d_screen, 0);
	wall_affine.a = (arch->decal.y - arch->decal.x) / (arch->depth.y - arch->depth.x);
	wall_affine.b = arch->decal.x - wall_affine.x * arch->depth.x;
	//on optien la position
	inter = interpolation_linear(px_affine, wall_affine);

	//on doit recupere le pourcentage du la texture
	percent = inter.x / (arch->depth.y - arch->depth.x);

	//on a le pourcentage de la portion de mur par rapport au pixel

	//recuperer le pourcentage global



}