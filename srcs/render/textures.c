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

	px_affine = affine_def(arch->px.x / arch->sdl.d_screen, 0);

}