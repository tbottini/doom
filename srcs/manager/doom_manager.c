#include "doom_nukem.h"

int		secure_doom(t_doom *doom)
{
	int fd;

	if ((fd = open(TTFWOLF, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TTFIMPACT, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) < 0)
		return (-1);
	close(fd);
	ft_bzero(doom, sizeof(t_doom));
	return (0);
}

void	doom_exit(t_doom *doom)
{
	free(doom->zline);
	player_free(&doom->player);
	ui_free(&doom->ui);
	editor_free(&doom->edit);
	sdl_free(&doom->sdl);
	music_free(&doom->sound);
	effect_free(&doom->sound);
	Mix_Quit();
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
	designer_init(&doom->tool, doom->sdl);
	if (!editor_init(&doom->edit))
		return (NULL);
	if (!ui_init(&doom->ui))
		return (NULL);
	if (!player_init(&doom->player))
		return (NULL);
	if (!music_init(&doom->sound))
		return (NULL);
	if (!(doom->zline = (double*)malloc(sizeof(double) * doom->sdl.size.x)))
		return (NULL);
	zline_reset(doom);
	ui_by_sdl(doom, &doom->ui);
	SDL_RaiseWindow(doom->sdl.win);
	return (doom);
}
