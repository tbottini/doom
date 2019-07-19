#include <doom_nukem.h>

/*
**	si au moins l'un des pilier est hors frustum il passe pas l'extremite de
**	l'ecran, on determine laquelle avec une polarite (-1 == 0px et 1 == max)
**	si l'angle entre le joueur est les deux pillier est superieur a 180
**	la polarite de depart (position du premier pillier) s'inverse
*/
void		px_polarite(t_arch *arch)
{
	t_fvct2	angle;
	double	diff;
	int		polarite;

	angle.x = local_angle(arch->bound.b_left, arch->wall->pillar->angle);
	angle.y = local_angle(arch->bound.b_left, arch->wall->next->angle);

	diff = fabs(angle.x - angle.y);
	polarite = (arch->wall->next->angle > arch->bound.b_left ? -1 : 1) * (diff < 180 ? 1 : -1);
	arch->px.x = (polarite == -1) ? 0 : arch->sdl->size.x -1;
	arch->px.y = arch->sdl->size.x - 1 - arch->px.x;
}

int			pillar_polarite(t_arch *arch, t_pillar *pillar, t_pillar *next)
{
	double	angle;
	double	angle_next;
	double	borne;

	angle = local_angle(arch->bound.b_left, pillar->angle);
	angle_next = local_angle(arch->bound.b_left, next->angle);
	borne = local_angle(arch->bound.b_left, arch->bound.b_right);


	if (angle < borne - 180)
		return (0);
	else if (angle > 180)
		return (arch->sdl->size.x - 1);
	else if (fabs(angle - angle_next) > 180)
		return (0);
	else
		return (arch->sdl->size.x - 1);
}

void			pillar_screen_info(t_arch *arch, t_player *p)
{
	float		angle;
	int			size;
	t_fvct2		tmp;

	size = arch->sdl->size.x;
	if (arch->wall->pillar->frust)
	{
		arch->px.x = fish_bowl_px(arch, *arch->wall->pillar);
		arch->depth.x = distance(*(t_fvct2*)&p->stat.pos, arch->wall->pillar->p);
		arch->decal.x = sin(arch->wall->pillar->angle * PI180) * arch->depth.x;
		arch->depth.x = cos(arch->wall->pillar->angle * PI180) * arch->depth.x;
		arch->shift_txtr.x = 1;
	}
	else
	{
		arch->px.x = pillar_polarite(arch, arch->wall->pillar, arch->wall->next);
		if (arch->px.x == 0)
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_left * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_left;
		}
		else
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_right * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_right;
		}
		arch->shift_txtr.x = wall_clipping(arch, p, &tmp, angle);
		arch->depth.x = tmp.x;
		arch->decal.x = tmp.y;
	}
	if (arch->wall->next->frust)
	{
		arch->px.y = fish_bowl_px(arch, *arch->wall->next);
		arch->depth.y = distance(*(t_fvct2*)&p->stat.pos, arch->wall->next->p);
		arch->decal.y = sin(arch->wall->next->angle * PI180) * arch->depth.y;
		arch->depth.y = cos(arch->wall->next->angle * PI180) * arch->depth.y;
		arch->shift_txtr.y = 0;
	}
	else
	{
		arch->px.y = pillar_polarite(arch, arch->wall->next, arch->wall->pillar);
		if (arch->px.y == 0)
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_left * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_left;
		}
		else
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_right * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_right;
		}
		arch->shift_txtr.y = wall_clipping(arch, p, &tmp, angle);
		arch->depth.y = tmp.x;
		arch->decal.y = tmp.y;
	}
}

/*
**	renvoie la position du mur par rapport au portail de rendu
**		0 si le portail est devant le portail
**		1 si le portail est derriere le portail
*/
int				wall_behind_portal(t_arch *arch)
{
	t_affine	a_wall;
	t_affine	a_portal;

	t_affine	a_pillar;
	t_affine	a_pillar2;
	t_fvct2		inter;
	t_fvct2		inter2;

	if (debug == 1)
		d_wall(arch->wall);

	a_pillar.a = arch->decal.x / arch->depth.x;
	a_pillar.b = 0;
	a_pillar2.a = arch->decal.y / arch->depth.y;
	a_pillar2.b = 0;
	draw_affine(arch, a_pillar, BLUE_SOFT);
	draw_affine(arch, a_pillar2, BLUE_SOFT);



	if (arch->bound.depth_portal.x == arch->bound.depth_portal.y)
	{
		a_portal.lock = 1;
		a_portal.b = arch->bound.depth_portal.x;
	}
	else
	{
		a_portal.lock = 0;
		a_portal.a = (arch->bound.decal_portal.y - arch->bound.decal_portal.x)
			/ (arch->bound.depth_portal.y - arch->bound.depth_portal.x);
		a_portal.b = arch->bound.decal_portal.x - (arch->bound.depth_portal.x * a_portal.a);
	}
	inter = interpolation_linear(a_portal, a_pillar);
	inter2 = interpolation_linear(a_portal, a_pillar2);
	//b_point_debug(arch, inter, RED);

	//si les deux pillier sont en dehors du portail on n'affiche pas la fonction
	if (inter.x > arch->depth.x && inter2.x > arch->depth.y)
		return (0);
	if (arch->depth.x == arch->depth.y)
	{
		a_wall.lock = 1;
		a_wall.b = arch->depth.x;
	}
	else
	{
		a_wall.lock = 0;
		a_wall.a = (arch->decal.y - arch->decal.x) / (arch->depth.y - arch->depth.x);
		a_wall.b = arch->decal.x - a_wall.a * arch->depth.x;
	}
	if (interpolation_linear_secur(a_portal, a_wall, &inter))
		return (0);

	draw_affine(arch, a_portal, YELLOW);
	draw_affine(arch, a_wall, GREEN);
	if (inter.x > arch->depth.x)
	{
		//le pillier x (!= y) est en dehors du portail
		b_point_debug(arch, inter, RED);
		//arch->depth.x = inter.x
		//arch->decal.x = inter.y;
	}
	else
	{
		//arch->depth.y = inter.x;
		//arch->decal.y = inter.y;
	}
	//else
	//{
	//	arch->depth.y = inter2.x;
	//	arch->decal.y = inter2.y;
	//	arch->shift_txtr.y =
	//	//depth.y decal.y shift_txtr.y
	//}

	/*

	inter = interpolation_linear(a_portal, a_pillar2);
	b_point_debug(arch, inter, RED);
	if (inter.x > arch->depth.y)
	{
		//le pillier de droite est en dehors du secteur
		//on modifie shift_txtr.y, decal.y, depth.y
		return (0);
	}*/
	return (1);
}

int			wall_screen_info(t_arch *arch, t_player *p)
{
	int		result;

	pillar_screen_info(arch, p);
	if (debug == 1)
		printf(WRED"portal:\n%f %f --> %f %f\n"WEND, arch->bound.depth_portal.x, arch->bound.decal_portal.x, arch->bound.depth_portal.y, arch->bound.decal_portal.y);
	if (arch->depth_portal > 0)
	{
		result = wall_behind_portal(arch);
		if (debug == 1)
			printf("wall_behind_portal %d\n\n", result);
		return (result);
	}

	return (1);
}
