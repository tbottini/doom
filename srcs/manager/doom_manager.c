#include "doom_nukem.h"

int		secure_doom(t_doom *doom)
{
	int fd;

	if ((fd = open(TTFWOLF, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TTFIMPACT, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALLBLUE, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALL, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(GOLD, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TEST, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	ft_bzero(doom, sizeof(t_doom));
	return (0);
}

void	doom_exit(t_doom *doom)
{
	player_free(&doom->player);
	ui_free(&doom->ui);
	editor_free(&doom->edit);
	sdl_free(&doom->sdl);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	free(doom);
	exit(0);
}

t_doom	*doom_init()
{
	t_doom	*doom;

	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		return (NULL);
	if (secure_doom(doom))
		return (NULL);
	if (!sdl_init(&doom->sdl, "Doom-Nukem"))
		return (NULL);
	if (!editor_init(&doom->edit))
		return (NULL);
	if (!ui_init(&doom->ui))
		return (NULL);
	if (!player_init(&doom->player))
		return (NULL);
	ui_by_sdl(doom, &doom->ui);
	return (doom);
}
