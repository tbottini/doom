#include "doom_nukem.h"

void	sdl_present(t_sdl *sdl)
{
	SDL_RenderCopy(sdl->rend, sdl->txture, NULL, NULL);
	SDL_RenderPresent(sdl->rend);
}

/*
** A utiliser entre deux fonctions pour calculer le temps de latence
** (better use in loop_hook and stuff)
** calcdelay("begin", doom);
** printf("Je suis une fonction lente\n");
** calcdelay("end", doom);
*/

void	sdl_cleartexture(Uint32 *screen, t_vct2 size)
{
	int x;

	x = -1;
	while (++x < size.x * size.y)
	{
		if (screen[x])
			screen[x] = 0;
	}
}

void calcdelay(const char *str, t_doom *doom)
{
	printf(" %s %u |", str, SDL_GetTicks() - doom->timestamp);
	doom->timestamp = SDL_GetTicks();
}
