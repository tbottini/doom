#include "doom_nukem.h"

# define PADDING 0.30
# define PADDING2 0.60
# define EPSILON 0.001

static int orientation(t_fvct3 p, t_fvct3 q, t_fvct3 r)
{
	double val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2)
{
	//int o1;
	//int o2;
	//int o3;
	//int o4;

	//o1 = orientationV42(p1, q1, p2);
	//o2 = orientationV42(p1, q1, q2);
	//o3 = orientationV42(p2, q2, p1);
	//o4 = orientationV42(p2, q2, q1);
	if (orientation(p1, q1, p2) != orientation(p1, q1, q2)
		&& orientation(p2, q2, p1) != orientation(p2, q2, q1))
		return (1);
	return (0);
}

t_wall		*collisionV21(t_doom *doom, t_fvct3 ori, t_fvct3 pos, t_wall *w)
{
	int		i;
	int		j;

	if (w)
	{
		if (vector_intersect(ori, pos, *(t_fvct3*)&w->pillar.p, *(t_fvct3*)&w->next->p))
			return (w);
		return (0);
	}
	i = -1;
	while (++i < doom->sector->len)
		if (vector_intersect(ori, pos, *(t_fvct3*)&doom->sector->wall[i].pillar.p, *(t_fvct3*)&doom->sector->wall[i].next->p))
			return (&doom->sector->wall[i]);
	j = -1;
	while (++j < doom->sector->len_sub)
	{
		i = -1;
		while (++i < doom->sector->ssector[j].len)
			if (vector_intersect(ori, pos, *(t_fvct3*)&doom->sector->ssector[j].wall[i].pillar.p, *(t_fvct3*)&doom->sector->ssector[j].wall[i].next->p))
				return (&doom->sector->ssector[j].wall[i]);
	}
	return (NULL);
}

t_wall		*collision(t_doom *doom, t_fvct3 pos, t_wall *w)
{
	t_fvct3 tmp;

	tmp.x = pos.x;
	tmp.y = pos.y + PADDING;
	pos.x += PADDING;
	if ((w = collisionV21(doom, pos, tmp, w)))
		return (w);
	tmp.y -= PADDING2;
	if ((w = collisionV21(doom, pos, tmp, w)))
		return (w);
	pos.x -= PADDING2;
	if ((w = collisionV21(doom, pos, tmp, w)))
		return (w);
	tmp.y += PADDING2;
	if ((w = collisionV21(doom, pos, tmp, w)))
		return (w);
	return (NULL);
}
