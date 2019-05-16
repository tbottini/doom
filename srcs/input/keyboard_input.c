#include "doom_nukem.h"

int		is_movekey(SDL_Keycode key)
{
	return (key == SDLK_w || key == SDLK_s || key == SDLK_d || key == SDLK_a);
}

int		is_rotkey(SDL_Keycode key)
{
	return (key == SDLK_q || key == SDLK_e);
}

void	debug_input(t_doom *doom, SDL_Keycode key)
{
	if (key == SDLK_f)
	{
		describe_sector_recursif(*doom->sector);
	}
}

void	move_input(t_doom *doom, SDL_Keycode key)
{
	if (key == SDLK_w)
		ft_putendl("avancer");
	else if (key == SDLK_s)
		ft_putendl("reculer");
	else if (key == SDLK_d)
		ft_putendl("droite");
	else if (key == SDLK_a)
		ft_putendl("gauche");
	(void)doom;
}

void	rot_input(t_doom *doom, SDL_Keycode key)
{
	if (key == SDLK_e)
		doom->player.rot.y -= 5;
	else if (key == SDLK_q)
		doom->player.rot.y += 5;
	doom->player.rot.y = double_modulo(doom->player.rot.y);
}

int		keyboard_input(t_doom *doom, SDL_Event event)
{
	SDL_Keycode key;

	key = event.key.keysym.sym;
	if (is_movekey(key))
		move_input(doom, key);
	else if (is_rotkey(key))
		rot_input(doom, key);
	else if (key == SDLK_f)
		debug_input(doom, key);
	else if (key == SDLK_ESCAPE)
		doom_exit(doom);
	portal_engine(doom);
	return (1);
}
