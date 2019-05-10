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

//int			pillar_info()
//{
//	if (bunch[i]->frust && !bunch[i + 1]->frust)
//	{
//		px = doom->sdl.size.x - 1;
//		dist = wall_clipping(*bunch[i], *bunch[i + 1], player.pos, player.rot.y + player.fov / 2.0);
//	}
//	else if (bunch[i + 1]->frust && !bunch[i]->frust)
//	{
//		px = 0;
//		dist = wall_clipping(*bunch[i], *bunch[i + 1], player.pos, double_modulo(player.rot.y - player.fov / 2.0));
//	}
//	else
//	{
//		px = ((float)(doom->sdl.size.x - 1) / 2.0) - (float)(doom->sdl.size.x) / player.fov * bunch[i]->angle;
//		dist = distance(player.pos, bunch[i]->pillar);
//	}
//}
//
//void		draw_part(t_sdl *sdl, t_wall, int *i)
//{
//
//}
//
//
//void		draw_wall(t_doom doom , t_wall wall)
//{
//	t_fvct2	dist;
//	t_vct2	px;
//	int		i;
//
//	i = get_column_id()
//}