#include "sector.h"
#include "debug.h"

t_sector		*sector_new()
{
	t_sector	*new;

	new = (t_sector *)malloc(sizeof(t_sector));
	if (!new)
		return (NULL);
	new->gravity.x = 0;
	new->gravity.y = 0;
	new->gravity.z = G_MOON;
	new->enemys = NULL;
	return (new);
}

void			sector_props_init(t_sector *sector)
{
	prop_iter(sector->props, sector->len_prop, &prop_init);
}

void			sector_wall_props_init(t_sector *sector)
{
	int			i;

	i = 0;
	while (i < sector->len)
	{
		prop_iter(sector->wall[i].props, sector->wall[i].nb_props, &prop_init);
		i++;
	}
}

void			sector_iter(t_sector *sector, int len, void (sector_effector)(t_sector*))
{
	int			i;

	i = 0;
	while (i < len)
	{
		sector_effector(&sector[i]);
		i++;
	}
}