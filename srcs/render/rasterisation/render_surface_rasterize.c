#include "doom_nukem.h"

void			print_triangle(t_triangle *triangle)
{
	printf("triangle\n");
	printf("v0: %f %f %f\n", triangle->v0.x, triangle->v0.y, triangle->v0.z);
	printf("v1: %f %f %f\n", triangle->v1.x, triangle->v1.y, triangle->v1.z);
	printf("v2: %f %f %f\n", triangle->v2.x, triangle->v2.y, triangle->v2.z);
}

/*
**	trie dans l'ordre les triangles
*/
int				triangles_in_frustum(t_fvct3 **tri)
{
	int			i;
	bool		sort;
	t_fvct3		*tmp;

	i = 0;
	sort = false;
	while (!sort)
	{
		sort = true;
		while (i < 2)
		{
			if (tri[i]->y > tri[i + 1]->y)
			{
				tmp = tri[i];
				tri[i] = tri[i + 1];
				tri[i + 1] = tmp;
				sort = false;
			}
			i++;
		}
		i = 0;
	}
	return ((tri[0]->y > 1) + (tri[1]->y > 1) + (tri[2]->y > 1));
}

int				clipping_depth(t_fvct3 *verticle2, t_fvct3 *verticle1)
{
	if (verticle2->y < 1 && verticle1->y < 1)
		return (1);
	else if (verticle2->z < 1)
		clipping_z(verticle2, verticle1);
	else if (verticle1->z < 1)
		clipping_z(verticle1, verticle2);
	return (0);
}

/*
**	on va clipper un triangle en deux sous triangles sans verticles derriere l'ecran
*/
void		triangle_zclipping2(t_arch *arch, t_screen *screen, t_fvct3 **clip_vct)
{
	t_fvct3		i1;
	t_fvct3		i2;
	t_triangle	new;

	i1 = *clip_vct[0];
	i2 = *clip_vct[0];
	clipping_z(&i1, clip_vct[1]);
	clipping_z(&i2, clip_vct[2]);
	new.v0 = i1;
	new.v1 = i2;
	new.v2 = *clip_vct[1];
	*clip_vct[0] = i2;

	camera_to_screen(&new, arch->cam, arch->sdl);
	triangle_show_verticles(screen, &new);
}


void			render_triangle(t_arch *arch, t_triangle *tri)
{
	int			clip;
	t_fvct3		*verticles_clip[3];
	t_screen	screen_tmp;

	screen_tmp = (t_screen){arch->sdl->screen, arch->sdl->size.x, arch->sdl->size.y};
	verticles_clip[0] = &tri->v0;
	verticles_clip[1] = &tri->v1;
	verticles_clip[2] = &tri->v2;
	clip = triangles_in_frustum(verticles_clip);
	if (clip == 0)
		return ;
	else if (clip == 1)
	{
		clipping_z(verticles_clip[2], verticles_clip[0]);
		clipping_z(verticles_clip[1], verticles_clip[0]);
		return ;
		//on recupere le vecteur dans le frustum
		//on raccourcis les autre verticles
	}
	else if (clip == 2)
	{
		//on modifie le triangle et on en rend un
		triangle_zclipping2(arch, &screen_tmp, verticles_clip);
	}
	camera_to_screen(tri, arch->cam, arch->sdl);
	triangle_show_verticles(&screen_tmp, tri);
}

//t_sdl
void			render_surface_rasterize(t_arch *arch, t_wall *surface, t_sector *sector, t_player *player)
{
	t_verticle		quad[4];
	t_triangle	triangles[2];

	surface_to_quad(&quad, surface, sector);
	quad_set_referential(&quad, &player->stat);
	quad_to_triangle(&quad, &triangles[0], &triangles[1]);

	triangles[0] = (t_triangle)
	{
		.v0 = (t_fvct3){-4, -70, -1},
		.v1 = (t_fvct3){-4, 70, -1},
		.v2 = (t_fvct3){0, 70, -1}
	}; //!!!! test floor
	triangles[1] = (t_triangle)
	{
		.v0 = (t_fvct3){0, -70, -1},
		.v1 = (t_fvct3){-4, -70, -1},
		.v2 = (t_fvct3){0, 70, -1}
	}; //!!!! test floor
	render_triangle(arch, &triangles[0]);
	render_triangle(arch, &triangles[1]);
}
