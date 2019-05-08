#include "doom_nukem.h"

int main(int ac, char **av)
{
	t_doom		*doom;

	if (ac < 2)
	{
		ft_putendl("no args");
		return (0);
	}
	doom = (t_doom*)malloc(sizeof(t_doom));
	if (!parsing(doom, av[1]))
	{
		ft_putendl("bad parsing");
		return (0);
	}
	return (0);
}