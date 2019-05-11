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

void calcdelay(const char *str, t_doom *doom)
{
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	printf(" %s %lu |", str, (spec.tv_sec * 1000000 + spec.tv_nsec / 1000) - doom->timestamp);
	doom->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
}
