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
	free(doom->tool.zline);
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
	if (!designer_init(&doom->tool, &doom->sdl, &doom->camera))
		return (NULL);
	if (!editor_init(&doom->edit))
		return (NULL);
	if (!ui_init(&doom->ui))
		return (NULL);
	if (!player_init(&doom->player))
		return (NULL);
	if (!music_init(&doom->sound))
		return (NULL);
	ui_by_sdl(doom, &doom->ui);
	SDL_RaiseWindow(doom->sdl.win);
	return (doom);
}
