#include "doom_nukem.h"

int	keyboard_input(t_doom *doom, SDL_Event event)
{
	SDL_Keycode key;

	key = event.key.keysym.sym;
	if (key == SDLK_e)
		doom->player.rot.y -= 5;
	else if (key == SDLK_q)
		doom->player.rot.y += 5;
	else if (key == SDLK_RETURN)
		portal_engine(doom);
	else if (key == SDLK_ESCAPE)
		doom_exit(doom);
	doom->player.rot.y = double_modulo(doom->player.rot.y);
	printf("rotation====%f====\n", doom->player.rot.y);
	portal_engine(doom);
	return (1);
}
