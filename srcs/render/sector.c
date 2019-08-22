#include "sector.h"

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
	//prop_iter(sector->props, sector->len_prop, &prop_init);
	(void)sector;
}


void			sector_wall_props_init(t_sector *sector)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < sector->len)
	{
		//printf("wall %d %f %f %f %f\n", i, sector->wall[i].next->p.x, sector->wall[i].next->p.y,
		//	sector->wall[i].pillar->p.x, sector->wall[i].pillar->p.y);
		while (j <= sector->wall[i].nb_props)
		{
			//printf("\twall %d %f %f %f %f\n", i, sector->wall[i].next->p.x, sector->wall[i].next->p.y,
			//sector->wall[i].pillar->p.x, sector->wall[i].pillar->p.y);
			prop_init(&sector->wall[i].props[j], &sector->wall[i]);
			j++;
		}
		j = 0;
		//prop_iter(sector->wall[i].props, sector->wall[i].nb_props, &prop_init);
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
