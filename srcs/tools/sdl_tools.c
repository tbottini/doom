#include "doom_nukem.h"

void	sdl_present(t_sdl *sdl)
{
	SDL_RenderCopy(sdl->rend, sdl->txture, NULL, NULL);
	SDL_RenderPresent(sdl->rend);
}