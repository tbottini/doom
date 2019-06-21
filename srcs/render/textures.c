#include "doom_nukem.h"

//on recupere le pixel on determine une affine
//on recupere les points projetes sur l'ecran
//				leurs pourcentages, position
//on en determine aussi une affine
//on fait une interpolation lineaire des deux
//on recupere le point d'intersection
//on definit un pourcentage dans le segment du mur
//on recupere la position u (largeur) dans la texture
//elle sera renvoyee

/*
**	renvoie le pourcentage global d'un pourcentage de pourcentage
*/
double			up_percent(double percent, double percent_part)
{
	return ((percent * percent_part) / (10000));
}


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


	//printf("--------interpolation--------\n");
	//on determine les affines du mur et du rayon joueur->px
	px_affine.a = ((arch->sdl->size.x / 2) - arch->px.x) / arch->cam->d_screen;
	px_affine.b = 0;
	//printf("pillar 1 decal %f depth %f\n", arch->decal.x, arch->depth.x);
	///printf("pillar 2 decal %f depth %f\n", arch->decal.y, arch->depth.y);
	if ((int)((arch->depth.y - arch->depth.x) * 100) == 0)
	{
		wall_affine.a = -1;
		wall_affine.b = arch->depth.x;
	}
	else
	{	//if (arch->px.x == 640)
		//	printf("different depth %f\n", arch->depth.y - arch->depth.x);
		wall_affine.a = (arch->decal.y - arch->decal.x) / (arch->depth.y - arch->depth.x);
		wall_affine.b = arch->decal.x - wall_affine.a * arch->depth.x;
	}
	//printf("px affine %f %f\n", px_affine.a, px_affine.b);
	//printf("wall affine %f %f\n", wall_affine.a, wall_affine.b);
	//on obtient la position
	inter = interpolation_linear(wall_affine, px_affine);

	//printf("inter %f %f\n", inter.x, inter.y);
	//on doit recuperer le pourcentage de la texture
	if ((int)((arch->decal.x - arch->decal.y) * 100) == 0)
		percent = (inter.x - arch->depth.x) / (arch->depth.y - arch->depth.x);
	else
		percent = (inter.y - arch->decal.x) / (arch->decal.y - arch->decal.x);

	//printf("percent %f\n", percent);
	//on a le pourcentage de la portion de mur par rapport au pixel
	//percent = up_percent(percent, arch->depth.x - arch->depth.y);
	//recuperation du pourcentage global

	if (percent > 1.0 || percent < -0.0001)
	{
		printf("-------\n");
		printf("px %d\n", arch->px.x);
		printf("arch->depth.x %f\n", arch->depth.x);
		printf("affine wall .a %f .b %f\n", wall_affine.a, wall_affine.b);
		printf("affine px .a %f .b %f\n", px_affine.a, px_affine.b);
		printf("inter.x %f\ninter.y %f\n", inter.x, inter.y);
		printf("decal %f\ndecal %f\n", arch->decal.x, arch->decal.y);
		printf("depth.x %f\ndepth.y %f\n", arch->depth.x, arch->depth.y);
		//printf("div %f\n", fabs(arch->decal.y - arch->decal.x));
		printf("percent %f\n", percent);
		printf("-------\n");
		//printf("inter.x %f %f\n", inter.x, inter.y);
	}

	//printf("----------------------------\n");
	return (percent * arch->wall->txtr.w);
}
