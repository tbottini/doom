#include "sector.h"
#include <SDL.h>

t_sector		*sector_new()
{
	t_sector	*new;

	new = (t_sector *)malloc(sizeof(t_sector));
	if (!new)
		return (NULL);
	new->len_sub = 0;
	new->gravity.x = 0;
	new->gravity.y = 0;
	new->gravity.z = G_MOON;
	new->enemys = NULL;
	return (new);
}
