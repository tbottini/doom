#include "doom_nukem.h"


/*
print un wall il faut

(px1, px2, dist1, dist2, sdl, texture1, texture2)

-determiner la colonne du pillier 1
-determiner la colomne du pillier 2
-determiner la distance des deux pillier
-determiner un coeficient
-faire un degrader jusqu'au pillier
*/

//il faut definir pillar et *next
//		une verification pa

//		si on est endehors du frustrum


void		pillar_screen_info(t_doom doom, t_wall wall, t_fvct2 *dist, t_vct2 *column_id)
{
	t_vct2 px;
	t_fvct2 d;
	t_player	*p;

	p = &doom.player;
	if (wall.pillar.frust)
	{
		px.x = (float)(doom.sdl.size.x) / 2.0;
		px.x -= (float)(doom.sdl.size.x - 1) / doom.player.fov * wall.pillar.angle;
		d.x = distance(p->pos, wall.pillar.p);
	}
	else if (wall.pillar.angle <= -doom.player.fov / 2.0)
	{
		px.x = doom.sdl.size.x - 1;
		d.x = wall_clipping(wall, p->pos, p->rot.y - p->fov / 2.0);
	}
	else if (wall.pillar.angle >= doom.player.fov / 2.0)
	{
		px.x = 0;
		d.x = wall_clipping(wall, p->pos, p->rot.y + p->fov / 2.0);
	}
	if (wall.next->frust)
	{
		px.y = (float)(doom.sdl.size.x) / 2.0;
		px.y -= (float)(doom.sdl.size.x - 1) / doom.player.fov * wall.next->angle;
		d.y = distance(p->pos, wall.next->p);
	}
	else if (wall.next->angle <= -doom.player.fov / 2.0)
	{
		px.y = doom.sdl.size.x - 1;
		d.y = wall_clipping(wall, p->pos, p->rot.y - p->fov / 2.0);
	}
	else if (wall.next->angle >= doom.player.fov / 2.0)
	{
		px.y = 0;
		d.y = wall_clipping(wall, p->pos, p->rot.y + p->fov / 2.0);
	}
	*column_id = px;
	*dist = d;
}

void		draw_wall(t_doom doom , t_wall wall)
{
	t_vct2	column_id;
	t_fvct2	dist;

	//test mur 1
	printf("--------------------test_mur----------------------------\n");
	fvct2_msg("pos pillar", wall.pillar.p);
	fvct2_msg("pos next", wall.next->p);
	pillar_screen_info(doom, wall, &dist, &column_id);
	printf("px pillar %d next %d\n dist pillar %f next %f\n", column_id.x, column_id.y, dist.x, dist.y);
	printf("--------------------------------------------------------\n");
	//printf("pillar column id %d dist %f\n", column_id.x, dist.x);
	//printf("pillar2 column id %d dist %f\n", column_id.y, dist.y);
}