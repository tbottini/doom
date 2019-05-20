#include "doom_nukem.h"

# define PADDING 0.01

t_fvct3			wall_collide(t_wall wall, t_fvct3 pos, double angle)
{
	t_fvct3		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_ang;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar.p.x - pos.x;
	diff.y = wall.pillar.p.y - pos.y;
	diff2.x = wall.next->p.x - pos.x;
	diff2.y = wall.next->p.y - pos.y;
	coef_ang = tan(angle * PI180);
	if (diff2.x - diff.x < 0.001 && diff2.x - diff.x > -0.001)
	{
		inter.x = diff.x;
		inter.y = diff.x * coef_ang;
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (coef_ang - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (inter);
}

int		linear(t_fvct2 a, t_fvct2 b, t_fvct2 mid)
{
	if ((b.y - a.y) / (b.x - a.x) == (mid.y - a.y) / (mid.x - a.x))
		;
}

t_wall	get_wall(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->sector->len)
	{
		if ((doom->sector->wall[i].pillar.angle >= 0 && doom->sector->wall[i].next->angle < 0)
			|| (doom->sector->wall[i].pillar.angle < 0 && doom->sector->wall[i].next->angle >= 0))
			return (doom->sector->wall[i]);
		++i;
	}
	return (doom->sector->wall[0]);
}

double		colli_dist(t_fvct3 vct1, t_fvct3 vct2)
{
	t_fvct2	dist;

	dist.x = vct2.x - vct1.x;
	dist.y = vct2.y - vct1.y;
	return (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
}

int		collision(t_doom *doom, int key)
{
	t_fvct3 inter;
	t_wall wall;
	double dist;

	wall = get_wall(doom);
	inter = wall_collide(wall, doom->player.pos, doom->player.rot.y);
	dist = colli_dist(inter, doom->player.pos);
	printf("dist = %f\n", dist);
	if (dist < PADDING)
	{
		ft_putendl("WAOW"); return (0);
	}
	ft_putendl("return un plutot auautrchose");
	return (1);
}