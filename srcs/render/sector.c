#include "sector.h"
#include <SDL.h>

t_sector		*sector_new()
{
	t_sector	*new;

	new = (t_sector *)malloc(sizeof(t_sector));
	if (!new)
		return (NULL);
	new->ssector = NULL;
	new->len_sub = 0;
	new->gravity.x = 0;
	new->gravity.y = 0;
	new->gravity.z = -9.80665;
	return (new);
}
