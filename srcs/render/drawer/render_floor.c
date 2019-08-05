#include "render.h"
#include "debug.h"

t_fvct2			fvct2_rotation(t_fvct2 vector, double rotation)
{
	double		tmp_x;

	tmp_x = cos(rotation) * vector.x - sin(rotation) * vector.y;
	vector.y = sin(rotation) * vector.x + cos(rotation) * vector.y;
	vector.x = tmp_x;
	return (vector);
}

t_fvct2			fvct2_addition(t_fvct2 vector, t_fvct2 add)
{
	vector.x += add.x;
	vector.y += add.y;
	return (vector);
}

/*
**	angle en radian
**	on recupere un vecteur a partir de l'angle
*/
t_fvct2			fvct2_from_angle(double angle)
{
	t_fvct2		vector_dir;

	vector_dir.x = cos(angle);
	vector_dir.y = sin(angle);
	return (vector_dir);
}


/*
**	retourne une intersection avec le sol selon la rotation x du joueur
**	dans le referentiel du monde
**	-vecteur directeur de l'angle (rot.x + fov_vertical / 2)
**	-recuperation de la profondeur avec l'intersection au sol
**	-multiplication de la profondeur avec le ratio de distance avec le pillier pour recuperer
**		la difference sur .y avec l'intersection au sol
**		on a donc la profondeur (z avec l'intersection
								x avec le rapport
								y la hauteur du sol ne change pas)
**	-on change le inter.(x, y) (x et z) pour les passer dans le referentiel du monde
**		avec une rotation inverse du joueur sur y
**		et une translation avec la position du joueur
*/
t_fvct2			frustum_floor_intersection(t_fvct2 *pillar_pos, t_camera *camera, t_fvct2 *len_sector, t_stat *stat)
{
	t_fvct2		angle_vector;
	t_fvct2		inter;


	printf("fov_ver %f\n", camera->fov_ver);

	//on considere par default que la rot.y est a 0 --> sur doom par default a 90
	angle_vector = fvct2_from_angle((stat->rot.x - 90) * TO_RADIAN - (camera->fov_ver / 2));
	//ajoute la rotation.x - 90 * TO_RADIAN
	printf("angle_vector %f %f\n", angle_vector.x, angle_vector.y);

	if (angle_vector.y >= 0)
	{
		printf("angle_vector.y == 0 pas d'intersection avec le sol\n");
		return ((t_fvct2){0, 0});
	}

	inter.x = len_sector->y / angle_vector.y * angle_vector.x;
	printf("len_sector.y %f intersection selon x %f\n", len_sector->y, inter.x);

	inter.y = inter.x / pillar_pos->x * pillar_pos->y;
	printf("pillar_pos .x %f .y %f\ninter .x %f .y %f\n", pillar_pos->x, pillar_pos->y, inter.x, inter.y);

	t_fvct2		test;

	test = inter;
	inter = fvct2_rotation(inter, -stat->rot.y * TO_RADIAN);
	//printf("inter with rot (%.2f) (cam ref (with rotation)) .x %f .y %f\n", stat->rot.y, inter.x, inter.y);

	inter = fvct2_addition(inter, *(t_fvct2*)&stat->pos);
	//printf("inter (world_ref) .x %f .y %f\n", inter.x, inter.y);
	return (test);
}

t_fvct2			frustum_depth_intersection(t_camera *camera, t_stat *stat, double floor_diff)
{
	t_fvct2		angle_vector;
	t_fvct2		inter;


	printf("fov_ver %f\n", camera->fov_ver);
	printf(WBLUE"%f"WEND, stat->rot.x);
	//on considere par default que la rot.y est a 0 --> sur doom par default a 90
	angle_vector = fvct2_from_angle((stat->rot.x - 90) * TO_RADIAN - (camera->fov_ver / 2));
	//ajoute la rotation.x - 90 * TO_RADIAN
	printf("angle_vector %f %f\n", angle_vector.x, angle_vector.y);

	if (angle_vector.y >= 0)
	{
		printf("angle_vector.y == 0 pas d'intersection avec le sol\n");
		return ((t_fvct2){0, 0});
	}

	inter.x = floor_diff / angle_vector.y * angle_vector.x;
	printf("len_sector.y %f intersection selon x %f\n", floor_diff, inter.x);

	inter.y = 0;

	return (inter);
}

/*
**	rendu du sol
*/
void				render_floor()
{
	//t_verticles		verticle[4];

	//on recupere l'intersection avec le sol
	//on recupere la position au sol d'une bande de l'ecran
	//frustum_floor_intersection();

	//arch_to_quad();

	//quad_to_triangle();
	//render_triangle();
	//render_triangle();
}