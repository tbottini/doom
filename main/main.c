#include "doom_nukem.h"

t_triangle		triangle_gen(int number_gen)
{
	t_triangle	gen;

	if (number_gen == 1)
	{
		gen = (t_triangle)
		{
			.v0 = (t_fvct3){-4, -70, -1},
			.v1 = (t_fvct3){-4, 70, -1},
			.v2 = (t_fvct3){0, 70, -1}
		};
	}
	else if (number_gen == 2)
	{
		gen = (t_triangle)
		{
			.v0 = (t_fvct3){0, -70, -1},
			.v1 = (t_fvct3){-4, -70, -1},
			.v2 = (t_fvct3){0, 70, -1}
		};
	}
	else
	{
		gen = (t_triangle)
		{
			.v0 = (t_fvct3){0, -70, -1},
			.v1 = (t_fvct3){-4, -70, -1},
			.v2 = (t_fvct3){0, 70, -1}
		};
	}
	return (gen);
}

void		triangle_print(t_triangle tri)
{
	printf("Triangle\n");
	fvct3_msg("v0", tri.v0);
	fvct3_msg("v1", tri.v1);
	fvct3_msg("v2", tri.v2);
}

/*
**	test de clip de triangle avec un verticles derriere la cam
**	et division du carre forme par le carre
*/
int			test_clipping_z_2_ptr(t_fvct3 **clip_vct)
{
	t_fvct3		i1;
	t_fvct3		i2;
	t_triangle	new;

	//les verticles clip sont trie selon leurs profondeur

	i1 = *clip_vct[0];
	i2 = *clip_vct[0];
	//le verticles hors frustum est v0
	clipping_z(&i1, clip_vct[1]);
	clipping_z(&i2, clip_vct[2]);

	//on cree un nouveau triangle a partir des verticles clip
	fvct3_msg("inter 1", i1);
	fvct3_msg("inter 2", i2);
	new.v0 = i1;
	new.v1 = i2;
	new.v2 = *clip_vct[1];

	//on change les valeurs du verticles 0 (derriere l'ecran) par
		// l'intersection 2 car la liaison i2 n'est pas encore faite avec clip_vct[1]
	*clip_vct[0] = i2;

	printf("new\n");
	triangle_print(new);

	return (0);
}

int				test_clipping_z_1(t_fvct3 **verticles_clip)
{
	//les verticles hors frustum sont v1 et v2

	clipping_z(verticles_clip[0], verticles_clip[2]);
	clipping_z(verticles_clip[1], verticles_clip[2]);

	return (0);
}

int				test_draw_floor()
{
	t_triangle	triangle;
	t_fvct3		*verticles_clip[3];
	int			clip;

	triangle = triangle_gen(1);

	verticles_clip[0] = &triangle.v0;
	verticles_clip[1] = &triangle.v1;
	verticles_clip[2] = &triangle.v2;
	clip = triangles_in_frustum(verticles_clip);
	if (clip == 0)
		return (0);
	else if (clip == 1)
	{
		test_clipping_z_1(verticles_clip);
		return (0);
	}
	if (clip == 2)
	{
		test_clipping_z_2_ptr(verticles_clip);

		printf("triangle");
		triangle_print(triangle);
	}
	else
	{
		return (0);
	}
	return (1);
}


int			main(int ac, char **av)
{
	test_draw_floor();
	return (0);
}
