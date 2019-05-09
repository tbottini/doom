#include "sector.h"

t_sector		*sector_new()
{
	t_sector	*new;

	new = (t_sector *)malloc(sizeof(t_sector));
	if (!new)
		return (NULL);
	return (new);
}
