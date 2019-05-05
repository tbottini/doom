#include "doom_nukem.h"

int	keyboard_input(t_doom *doom, SDL_Event event)
{
	SDL_Keycode key;

	key = event.key.keysym.sym;
	if (key == SDLK_r)
		doom->player.rot.y += 5;
	else if (key == SDLK_q)
		doom->player.rot.y -= 5;
	else if (key == SDLK_ESCAPE)
		doom_exit(doom);
	//portal_engine(doom->player, doom->sector);
	return (1);
}