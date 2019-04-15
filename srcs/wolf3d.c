#include "wolf3d.h"

t_wolf			*wolf_new()
{
	t_wolf		*wolf;

	wolf = (t_wolf*)malloc(sizeof(t_wolf));
	if (!wolf)
		return (NULL);
	wolf->data = sdldata_start("Wolf 3D", 1920, 1080);
	if (!(wolf->data))
	{
		free(wolf);
		return (NULL);
	}
	wolf->position.x = 0;
	wolf->position.y = 0;
	return (wolf);
}

void			wolf_close(t_wolf **wolf)
{
	sdldata_quit(&(*wolf)->data);
	free(*wolf);
	exit(0);
}

int				main(int ac, char **av)
{
	t_wolf		*wolf;

	wolf = NULL;
	wolf = wolf_new();
	if (!wolf)
		return (0);
	//if (!wolf_parseur(ac, av, wolf))
	//{
		//ft_putendl("error");
		//return (0);
	//}
	//raythrowing(wolf, 1650);
	wolf_close(&wolf);
	return (0);
}
