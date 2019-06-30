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
	free(doom->arch.zline);
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
		doom_exit(doom);
	if (secure_doom(doom))
		doom_exit(doom);
	if (!sdl_init(&doom->sdl, "Doom-Nukem"))
		doom_exit(doom);
	if (!designer_init(&doom->arch, &doom->sdl, &doom->camera))
		doom_exit(doom);
	if (!editor_init(&doom->edit))
		doom_exit(doom);
	if (!ui_init(&doom->ui))
		doom_exit(doom);
	player_init(&doom->player);
	if (!music_init(&doom->sound))
		doom_exit(doom);
	ui_by_sdl(doom, &doom->ui);
	SDL_RaiseWindow(doom->sdl.win);
	return (doom);
}
