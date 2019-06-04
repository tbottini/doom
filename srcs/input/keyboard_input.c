#include "doom_nukem.h"

int		is_rotkey(SDL_Keycode key)
{
	return (key == SDLK_q || key == SDLK_e || key == SDLK_r || key == SDLK_f);
}

int		is_movekey(SDL_Keycode key)
{
	return (key == SDLK_w || key == SDLK_s || key == SDLK_d || key == SDLK_a);
}

void	mvt_input(t_player *player, int key)
{
	double angle;
	t_fvct2	next_pos;

	angle = player->rot.y;
	if (key == SDLK_a)
		angle += 90;
	else if (key == SDLK_d)
		angle += 270;
	else if (key == SDLK_s)
		angle += 180;
	if (angle >= 360)
		angle -= 360;
	next_pos.x += player->pos.x + (cos(angle * PI180) / 10.0);
	next_pos.y += player->pos.y + (sin(angle * PI180) / 10.0);
	if (next_pos.x < 0 || next_pos.y < 0)
		return ;
	player->pos.x = next_pos.x;
	player->pos.y = next_pos.y;
}

void	debug_input(t_doom *doom, SDL_Keycode key)
{
	if (key == SDLK_f)
	{
		describe_sector_recursif(*doom->sector);
	}
}

void	rot_input(t_doom *doom, SDL_Keycode key)
{
	if (key == SDLK_e)
		doom->player.rot.y -= 5;
	else if (key == SDLK_q)
		doom->player.rot.y += 5;
	//else if (key == SDLK_r && doom->player.rot.x + 5 < 180)
	//	doom->player.rot.x += 5;
	//else if (key == SDLK_f && doom->player.rot.x - 5 > 0)
	//	doom->player.rot.x -= 5;
	else if (key == SDLK_r)
		doom->player.sector->h_ceil += 0.5;
	else if (key == SDLK_f)
		doom->player.sector->h_ceil -= 0.5;
	//printf("player rot %f %f\n", doom->player.rot.x, doom->player.rot.y);
	doom->player.rot.y = double_modulo(doom->player.rot.y);
}

int		keyboard_input(t_doom *doom, SDL_Event event)
{
	SDL_Keycode key;

	key = event.key.keysym.sym;
	if (is_rotkey(key))
		rot_input(doom, key);
	else if (is_movekey(key))
		mvt_input(&doom->player, key);
	else if (key == SDLK_f)
		debug_input(doom, key);
	else if (key == SDLK_ESCAPE)
		doom_exit(doom);
	doom_render(doom);
	return (1);
}
