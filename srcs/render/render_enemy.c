#include "render.h"

void			render_enemy(t_sdl *sdl, t_enemy enemy)
{

}

void			render_sector_enemy(t_sdl *sdl, t_sector *sector)
{
	t_enemy		*enemy_node;

	enemy_node = sector->enemys;
	if (!enemy_node)
		printf("pas d'ennemis\n");
	while (enemy_node)
	{
		enemy_node = enemy_node->next;
	}

}