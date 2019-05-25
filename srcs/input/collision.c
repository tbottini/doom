#include "doom_nukem.h"

# define PADDING2 0.3
# define PADDING 0.5
# define EPSILON 0.001

t_fvct3			wall_collide(t_wall wall, t_fvct3 pos, double angle)
{
	t_fvct3		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar.p.x - pos.x;
	diff.y = wall.pillar.p.y - pos.y;
	diff2.x = wall.next->p.x - pos.x;
	diff2.y = wall.next->p.y - pos.y;
	angle = tan(angle * PI180);
	if (diff2.x - diff.x < 0.001 && diff2.x - diff.x > -0.001)
	{
		inter.x = diff.x;
		inter.y = diff.x * angle;
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (angle - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (inter);
}

t_wall	get_wall(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->sector->len)
	{
		if (doom->sector->wall[i].pillar.angle >= 0 && doom->sector->wall[i].next->angle < 0
			&& (doom->sector->wall[i].pillar.angle - doom->sector->wall[i].next->angle) < 180)
		{
			printf("i = %d\n", i);
			return (doom->sector->wall[i]);
		}
		else if (doom->sector->wall[i].pillar.angle < 0 && doom->sector->wall[i].next->angle >= 0
			&& doom->sector->wall[i].next->angle - doom->sector->wall[i].pillar.angle < 180)
		{
			printf("i = %d\n", i);
			return (doom->sector->wall[i]);
		}
		++i;
	}
	return (doom->sector->wall[0]);
}
/*
double		colli_dist(t_fvct3 vct1, t_fvct3 vct2)
{
	t_fvct2	dist;

	//dist.x = vct2.x - vct1.x;
	//dist.y = vct2.y - vct1.y;
	(void)vct1;
	dist.x = vct2.x;
	dist.y = vct2.y;
	return (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
}

int		collision(t_doom *doom, int key)
{
	t_fvct3 inter;
	t_wall wall;
	double dist;

	wall = get_wall(doom);
	inter = wall_collide(wall, doom->player.pos, doom->player.rot.y);
	printf("pers : x = %f | y = %f\n", doom->player.pos.x, doom->player.pos.y);
	printf("inter : x = %f | y = %f\n", inter.x, inter.y);
	dist = colli_dist(doom->player.pos, inter);
	printf("dist = %f\n\n", dist);
	//printf("x = %f | y = %f\n", inter.x, inter.y);
	if (dist < PADDING)
		return (1);
	if ((fabs(inter.x) <= PADDING && fabs(inter.y) <= PADDING2)
		||(fabs(inter.y) <= PADDING && fabs(inter.x) <= PADDING2))
		return (1);
	return (0);
}

//==========================================V2===================================================//

t_wall	get_wall2(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->sector->len)
	{
		if (doom->sector->wall[i].pillar.angle >= 0 && doom->sector->wall[i].next->angle < 0
			&& (doom->sector->wall[i].pillar.angle - doom->sector->wall[i].next->angle) < 180)
			return (doom->sector->wall[i]);
		if (doom->sector->wall[i].pillar.angle < 0 && doom->sector->wall[i].next->angle >= 0
			&& doom->sector->wall[i].next->angle - doom->sector->wall[i].pillar.angle < 180)
			return (doom->sector->wall[i]);
		++i;
	}
	return (doom->sector->wall[0]);
}

int		collision3(t_doom *doom, t_fvct3 m1, t_fvct3 m2)
{
	double	ap;
	double	am;
	double	bp;
	double	bm;
	double	tmp;

	am = (m2.y - m1.x) / (m2.x - m1.x);
	ap = (doom->player.vel.y) / (doom->player.vel.x);
	if (ap == am)
		return (1);
	bm = m1.y - (am * m1.x);
	bp = doom->player.pos.y - (ap * doom->player.pos.x);
	tmp = (bp - bm) / (am - ap);
	if (fabs(tmp) + fabs(doom->player.pos.x) < fabs(doom->player.vel.x) + fabs(doom->player.pos.x))
		return (0);
	return (1);
}

int		collision4(t_doom *doom)
{
	t_wall	wall;
	t_fvct3 inter1;
	t_fvct3 inter2;

	wall = get_wall2(doom);
	inter1.x = wall.pillar.p.x;
	inter1.y = wall.pillar.p.y;
	inter2.x = wall.next->p.x;
	inter2.y = wall.next->p.y;
	return (collision3(doom, inter1, inter2));
}

//=====================================V3======================================//

int		direction(t_fvct3 a, t_fvct3 b, t_fvct3 c)
{
	double res;

	res = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (!res)
		return (0);
	return (res < 0 ? -1 : 1);
}

int		on_line(t_fvct3 a, t_fvct3 l1, t_fvct3 l2)
{
	//if (a.x <= fmax(l1.x, l2.x) && a.x >= fmin(l1.x, l2.x)
	//	&& a.y <= fmax(l1.y, l2.y) && a.y >= fmin(l1.y, l2.y))
	//	return (1);
	double s1;
	double s2;

	s1 = (l1.y - l2.y) / (l1.x - l2.x);
	s2 = (l1.y - a.y) / (l1.x - a.x);
	if (s1 == s2)
		return (1);
	return (0);
}

int		test(char *str, int i)
{
	ft_putendl(str);
	return (i);
}

int		collision6(t_fvct3 p1, t_fvct3 p2, t_fvct3 q1, t_fvct3 q2)
{
	int dir1;
	int dir2;
	int dir3;
	int dir4;

	dir1 = direction(p1, p2, q1);
	dir2 = direction(p1, p2, q2);
	dir3 = direction(q1, q2, p1);
	dir4 = direction(q1, q2, p2);
	if (dir1 != dir2 && dir3 != dir4)
		return (test("0", 1)); //return (1);
	if (dir1 == 0 && on_line(q1, p1, p2))
		return (test("1", 1)); //return (1);
	if (dir2 == 0 && on_line(q2, p1, p2))
		return (test("2", 1)); //return (1);
	if (dir3 == 0 && on_line(p1, q1, q2))
		return (test("3", 1)); //return (1);
	if (dir4 == 0 && on_line(p2, q1, q2))
		return (test("4", 1)); //return (1);
	return (0);
}

int		collision5(t_doom *doom)
{
	t_wall	wall;
	t_fvct3 inter1;
	t_fvct3 inter2;
	t_fvct3 p2;

	wall = get_wall2(doom);
	inter1.x = wall.pillar.p.x;
	inter1.y = wall.pillar.p.y;
	inter2.x = wall.next->p.x;
	inter2.y = wall.next->p.y;
	p2.x = doom->player.pos.x + doom->player.vel.x;
	p2.y = doom->player.pos.y + doom->player.vel.y;
	return (collision6(doom->player.pos, p2, inter1, inter2));
}

//==================================V4===========================================//

t_fvct3			wall_collide51(t_wall wall, t_fvct3 pos, double angle)
{
	t_fvct3		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar.p.x - pos.x;
	diff.y = wall.pillar.p.y - pos.y;
	diff2.x = wall.next->p.x - pos.x;
	diff2.y = wall.next->p.y - pos.y;
	angle = tan(angle * PI180);
	if (diff2.x - diff.x < 0.001 && diff2.x - diff.x > -0.001)
	{
		inter.x = diff.x;
		inter.y = diff.x * angle;
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (angle - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (inter);
}

int		intersect2(t_fvct3 p1, t_fvct3 p2, t_fvct3 inter)
{
	//(c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y)
	double cross;
	double dot;
	double squared;

	cross = (inter.y - p1.y) * (p2.x - p1.x) - (inter.x - p1.x) * (p2.y - p1.y);
	if (fabs(cross) > EPSILON)
		return (0);
	dot = (inter.x - p1.x) * (p2.x - p1.x) + (inter.y - p1.y) * (p2.y - p1.y);
	if (dot < 0)
		return (0);
	squared = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
	if (dot > squared)
		return (0);
	return (1);
}

int		intersect(t_fvct3 p1, t_fvct3 p2, t_fvct3 inter)
{
	//(c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y)
	double cross;
	double dot;
	double squared;

	cross = (inter.y - p1.y) * (p2.x - p1.x) - (inter.x - p1.x) * (p2.y - p1.y);
	if (fabs(cross) > EPSILON)
	{
		if (fmin(p1.x, p1.x) <= inter.x && fmax(p1.x, p2.x) >= inter.x
			&& fmin(p1.y, p1.y) <= inter.y && fmax(p1.y, p2.y) >= inter.y)
			return (1);
	}
	return (0);
}

int		collision51(t_doom *doom)
{
	t_wall	wall;
	//t_fvct3 inter1;
	//t_fvct3 inter2;
	t_fvct3 p2;
	t_fvct3 collide;

	wall = get_wall2(doom);
	collide = wall_collide51(wall, doom->player.pos, doom->player.rot.y);
	//inter1.x = wall.pillar.p.x;
	//inter1.y = wall.pillar.p.y;
	//inter2.x = wall.next->p.x;
	//inter2.y = wall.next->p.y;
	p2.x = doom->player.pos.x + doom->player.vel.x;
	p2.y = doom->player.pos.y + doom->player.vel.y;
	return (intersect(doom->player.pos, p2, collide));
}

//=====================================V5========================================//

int		intersection(t_fvct3 p1, t_fvct3 p2, t_fvct3 w1, t_fvct3 w2)
{
	t_fvct2 inter_xp;
	t_fvct2 inter_xw;
	t_fvct2 inter;
	double point;
	double a1;
	double a2;
	double b1;
	double b2;

	inter_xp.x = fmin(p1.x, p2.x);
	inter_xp.y = fmax(p1.x, p2.x);
	inter_xw.x = fmin(w1.x, w2.x);
	inter_xw.y = fmax(w1.x, w2.x);
	if (fmax(p1.x, p2.x) < fmin(w1.x, w2.x))
		return (0);
	a1 = (p1.y - p2.y) / (p1.x - p2.x);
	a2 = (w1.y - w2.y) / (w1.x - w2.x);
	if (fabs(a1 - a2) < EPSILON)
		return (0);
	b1 = p1.y - a1 * p1.x;
	b2 = w1.y - a2 * w1.x;
	inter.x = fmax(fmin(p1.x, p2.x), fmin(w1.x, w2.x));
	inter.y = fmin(fmax(p1.x, p2.x), fmax(w1.x, w2.x));
	point = (b2 - b1) / (a1 - a2);
	if (fabs((a1 * point + b1) - (a2 * point + b2)) < EPSILON)
	{
		if (point < inter.x || point > inter.y)
			return (0);
		else
			return (1);
	}
	return (0);
}

int		collision51k(t_doom *doom)
{
	t_wall	wall;
	t_fvct3 wall1;
	t_fvct3 wall2;
	t_fvct3 p2;

	wall = get_wall2(doom);
	wall1.x = wall.pillar.p.x;
	wall1.y = wall.pillar.p.y;
	wall2.x = wall.next->p.x;
	wall2.y = wall.next->p.y;
	p2.x = doom->player.pos.x + doom->player.vel.x;
	p2.y = doom->player.pos.y + doom->player.vel.y;
	return (intersection(doom->player.pos, p2, wall1, wall2));
}

//====================================V6========================================//

int		position(t_fvct3 a, t_fvct3 b, t_fvct3 c)
{
	double tmp;

	tmp = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if ((tmp < 0 && tmp > -EPSILON) || tmp < EPSILON)
		return (0);
	return (tmp > 0 ? 1 : -1);
}

int		cross(t_fvct3 p1, t_fvct3 p2, t_fvct3 w1, t_fvct3 w2)
{
	int a;
	int b;

	a = position(w1, w2, p1);
	b = position(w1, w2, p2);
	if (a == b)
		return (1);
	return (0);
}

int		collision51M(t_doom *doom)
{
	t_wall	wall;
	t_fvct3 wall1;
	t_fvct3 wall2;
	t_fvct3 p2;

	wall = get_wall2(doom);
	wall1.x = wall.pillar.p.x;
	wall1.y = wall.pillar.p.y;
	wall2.x = wall.next->p.x;
	wall2.y = wall.next->p.y;
	p2.x = doom->player.pos.x + doom->player.vel.x;
	p2.y = doom->player.pos.y + doom->player.vel.y;
	return (intersection(doom->player.pos, p2, wall1, wall2));
}
*/
//=====================================V7====================================//

t_wall	get_wallV7(t_doom *doom, int dir)
{
	int		i;
	int		min;
	int		max;
	double	angle;
	double	next;

	i = 0;
	//min = 0 + dir;
	//max = (180 + dir) % 360;
	min = 0;
	max = 180;
	while (i < doom->sector->len)
	{
		angle = doom->sector->wall[i].pillar.angle - dir;
		next = doom->sector->wall[i].next->angle - dir;
		if (angle >= min && next < min
			&& (angle - next) < max)
		{
			printf("i = %d\n", i);
			return (doom->sector->wall[i]);
		}
		else if (angle < min && next >= min
			&& next - angle < max)
		{
			printf("i = %d\n", i);
			return (doom->sector->wall[i]);
		}
		++i;
	}
	return (doom->sector->wall[0]);
}

double		distV7(t_fvct3 vct1, t_fvct3 vct2)
{
	t_fvct2	dist;

	dist.x = vct2.x;
	dist.y = vct2.y;
	return (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
}

int		collisionV72(t_player *player, t_wall wall, double angle)
{
	t_fvct3 inter;
	double dist;
	double dist2;
	double dist3;

	inter = wall_collide(wall, player->pos, angle);
	dist = distV7(player->pos, inter);
	inter = wall_collide(wall, player->pos, angle - (player->fov / 2));
	dist2 = distV7(player->pos, inter);
	inter = wall_collide(wall, player->pos, angle + (player->fov / 2));
	dist3 = distV7(player->pos, inter);
	printf("dist = %f || dist2 = %f || dist3 = %f\n\n", dist, dist2, dist3);
	if (dist < PADDING || dist2 < PADDING || dist3 < PADDING)
		return (1);
	return (0);
}

int		collisionV7(t_doom *doom, int key)
{
	t_wall wall;
	double	angle;
	int		dir;

	dir = 0;
	angle = doom->player.rot.y;
	if (key == SDLK_s)
	{
		angle += 180;
		dir = 180;
	}
	else if (key == SDLK_a)
	{
		angle += 90;
		dir = 90;
	}
	else if (key == SDLK_d)
	{
		angle += 270;
		dir = -90;
	}
	if (angle >= 360)
		angle -= 360;
	wall = get_wallV7(doom, dir);
	return (collisionV72(&doom->player, wall, angle));
}

//=====================================V42====================================//

int minV42(int a, int b)
{
	return (a < b ? a : b);
}

int maxV42(int a, int b)
{
	return (a > b ? a : b);
}

static int orientationV42(t_fvct3 p, t_fvct3 q, t_fvct3 r)
{
	double val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int vector_intersectV42(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2)
{
	int o1;
    int o2;
    int o3;
    int o4;

	o1 = orientationV42(p1, q1, p2);
    o2 = orientationV42(p1, q1, q2);
    o3 = orientationV42(p2, q2, p1);
    o4 = orientationV42(p2, q2, q1);
    if (o1 != o2 && o3 != o4)
        return (1);
    return (0);
}

int		collisionV42(t_doom *doom, t_fvct3 pos, int w)
{
	t_fvct3 futur;
	int i;

	if (w != -1)
		return (vector_intersectV42(doom->player.pos, pos, *(t_fvct3*)&doom->sector->wall[w].pillar.p, *(t_fvct3*)&doom->sector->wall[w].next->p));
	i = 0;
	while (i < doom->sector->len)
	{
		if (vector_intersectV42(doom->player.pos, pos, *(t_fvct3*)&doom->sector->wall[i].pillar.p, *(t_fvct3*)&doom->sector->wall[i].next->p))
			return (i);
		++i;
	}
	return (-1);
}

//===============================================================================//
//================================MOVE===========================================//
//===============================================================================//

void	super_move(t_doom *doom, t_player *player, int key)
{
	t_fvct2 d;
	t_fvct3 npos;

	// Update Rotation
	npos.z = player->pos.z;
	player->rot.y += player->rotvel.y;
	if (player->rot.y < 0.0)
		player->rot.y += 360.0;
	else if (player->rot.y > 360)
		player->rot.y -= 360.0;
	// Update Position
	if (collisionV7(doom, key))
		return (ft_putendl("BLOCKED"));
	d.x = sin(player->rot.y * PI180) / 10.0;
	d.y = cos(player->rot.y * PI180) / 10.0;
	npos.x = player->pos.x + d.x * doom->player.vel.y / 35000.0 + d.y * 1 * doom->player.vel.x / 35000.0;
	npos.y = player->pos.y - d.x * -doom->player.vel.x / 35000.0 - d.y * doom->player.vel.y / 35000.0;
	player->pos = npos;
}
