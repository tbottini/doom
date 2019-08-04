#include "rasterize.h"

void			print_triangle(t_triangle *triangle)
{
	printf("triangle\n");
	printf("v0: %f %f %f\n", triangle->v[0].p.x, triangle->v[0].p.y, triangle->v[0].p.z);
	printf("v1: %f %f %f\n", triangle->v[1].p.x, triangle->v[1].p.y, triangle->v[1].p.z);
	printf("v2: %f %f %f\n", triangle->v[2].p.x, triangle->v[2].p.y, triangle->v[2].p.z);
}

/*
**	trie dans l'ordre les triangles
*/
int				verticles_in_frustum(t_verticle **vert)
{
	int			i;
	bool		sort;
	t_verticle	*tmp;

	i = 0;
	sort = false;
	while (!sort)
	{
		sort = true;
		while (i < 2)
		{
			if (vert[i]->p.y > vert[i + 1]->p.y)
			{
				tmp = vert[i];
				vert[i] = vert[i + 1];
				vert[i + 1] = tmp;
				sort = false;
			}
			i++;
		}
		i = 0;
	}
	return ((vert[0]->p.y > 1) + (vert[1]->p.y > 1) + (vert[2]->p.y > 1));
}

/*
**	on va clipper un triangle en deux sous triangles sans verticles derriere l'ecran
*/
t_triangle		triangle_clip_split(t_verticle **clip_vct)
{
	t_verticle	i1;
	t_verticle	i2;
	t_triangle	new;

	i1 = *clip_vct[0];
	i2 = *clip_vct[0];
	verticle_clipping_z(&i1, clip_vct[1]);
	verticle_clipping_z(&i2, clip_vct[2]);
	new.v[0] = i1;
	new.v[1] = i2;
	new.v[2] = *clip_vct[1];
	*clip_vct[0] = i2;

	return (new);
}

void			render_triangle(t_camera *cam, t_sdl *sdl, t_triangle *tri)
{
	int			clip;
	t_verticle	*verticles_clip[3];
	t_screen	screen_tmp;
	t_triangle	triangle_divide;

	screen_tmp = (t_screen){sdl->screen, sdl->size.x, sdl->size.y};
	verticles_clip[0] = &tri->v[0];
	verticles_clip[1] = &tri->v[1];
	verticles_clip[2] = &tri->v[2];
	clip = verticles_in_frustum(verticles_clip);
	if (clip == 0)
		return ;
	else if (clip == 1)
	{
		verticle_clipping_z(verticles_clip[0], verticles_clip[2]);
		verticle_clipping_z(verticles_clip[1], verticles_clip[2]);
	}
	else if (clip == 2)
	{
		triangle_divide = triangle_clip_split(verticles_clip);
		triangle_cam_to_screen(&triangle_divide, cam, sdl);
		triangle_show_verticles(&screen_tmp, &triangle_divide);
	}
	triangle_cam_to_screen(tri, cam, sdl);
	triangle_show_verticles(&screen_tmp, tri);
}

//t_sdl
void			render_surface_rasterize(t_camera *cam, t_sdl *sdl, t_wall *surface, t_sector *sector, t_player *player)
{
	t_verticle		quad[4];
	t_triangle	triangles[2];

	if (surface->status == WALL)
	{
		surface_to_quad(&quad, surface, sector);
		quad_world_to_camera(&quad, &player->stat);
		quad_to_triangle(&quad, &triangles[0], &triangles[1]);
		render_triangle(cam, sdl, &triangles[0]);
		render_triangle(cam, sdl, &triangles[1]);
	}
}
