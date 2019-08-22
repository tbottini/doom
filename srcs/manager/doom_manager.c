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
	printf("doom exit\n");
	ui_free(&doom->ui);
	editor_free(doom);
	sdl_free(&doom->sdl);
	music_free(&doom->game.sound);
	effect_free(&doom->game.sound);

	doom->game.ui = NULL;

	//on free la borne de l'architecte
	borne_free(&doom->game.arch.portal);

	//on free les secteurs les pillier et les gamesurface et surfpath
	free_game(&doom->game);

	doom->game.sectors = 0;
	doom->game.pillars = 0;
	doom->game.gamesurf = 0;
	doom->game.surfpath = 0;
	doom->game.ui = 0;


	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	//game leaks
	ft_bzero(&doom->game, sizeof(t_game));
	ft_bzero(&doom->sdl, sizeof(t_sdl));
	ft_bzero(&doom->edit, sizeof(t_editor));
	ft_bzero(&doom->controller, sizeof(SDL_GameController*));
	ft_bzero(&doom->ui, sizeof(t_ui));
	ft_bzero(doom, sizeof(t_doom));
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
	if (!ui_init(&doom->ui))
		doom_exit(doom);
	ui_by_sdl(doom, &doom->ui);
	camera_init(&doom->game.camera, &doom->sdl, 90);
	if (!arch_init(&doom->game.arch, &doom->sdl, &doom->game.camera))
		doom_exit(doom);
	doom->edit.ui = &doom->ui;
	if (!editor_init(&doom->edit))
		doom_exit(doom);
	if (!music_init(&doom->game.sound))
		doom_exit(doom);
	doom->game.player.fov = 90;
	doom->game.ui = &doom->ui;
	doom->game.difficulty = MEDIUM;
	SDL_RaiseWindow(doom->sdl.win);
	doom->timestamp = SDL_GetTicks();
	doom->debug = 0;
	return (doom);
}
