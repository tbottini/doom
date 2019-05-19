/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/05/19 17:22:37 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when a key is pressed (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
	{
		doom->ui.curr_btn = NULL;
		sdl_set_status(doom, 1);
	}
	else if (key == SDLK_RETURN)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	else if (key == SDLK_SPACE)
		;//jump();
	else if (key == SDLK_v)
		;//kick(&(doom->player), /*sector*/);
	else if (key == SDLK_r)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDLK_e)
		action(doom);
	else if (key == SDLK_g)
		describe_player(doom->player);
	else if (key == SDLK_h)
		describe_sector(*doom->sector);
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	if (key == SDLK_w || key == SDLK_s)
	{
		doom->player.vel.x = 0;
	}
	else if (key == SDLK_a || key == SDLK_d)
	{
		doom->player.vel.y = 0;
	}
	else if (key == SDLK_q || key == SDLK_e)
	{
		doom->player.rotvel.y = 0.0;
	}
	else if (key == SDLK_LGUI)
		crouch_release(&doom->player);
	return (0);
}

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_btn *curr_btn;

	if (btn == SDL_BUTTON_LEFT)
	{
		doom->ui.curr_btn = NULL;
		curr_btn = btn_hover(doom, x, y);
		if (curr_btn && curr_btn->func)
			(*curr_btn->func)(doom);
		else
		{
			if (doom->ui.m_status != 0)
				btn_click(doom, x, y);/* Better wait from visual implementation
			else if (!(doom->player.weapons[doom->player.hand].rate))
				shoot(doom);
			else
				ft_nodeadd_int(&(doom->sdl.keys), SDL_BUTTON_LEFT);*/
		}
	}
	//else if (btn == SDL_BUTTON_RIGHT)
		//fire_on_off(doom->sdl.screen, doom->sdl.size, 0); // Debug thing
	else if (btn == SDL_BUTTON_X1)
		next_weapon(&(doom->player));
	else if (btn == SDL_BUTTON_X2)
		prev_weapon(&(doom->player));
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)btn;
	(void)x;
	(void)y;
//	if (btn == SDL_BUTTON_LEFT && doom->player.weapons[doom->player.hand].rate)
//		ft_noderm_int(&(doom->sdl.keys), btn);
	return (0);
}

/*
** Add here function that need to be done when mouse if moved in window
** x and y are relative postions when in gamemode
*/

int		mouse_move(int x, int y, t_doom *doom)
{
	//t_btn	*curr_btn;
	t_slid	*tmp;

	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	doom->ui.curr_btn = btn_hover(doom, x, y);
	if (doom->ui.m_status == 0)
	{
		//ft_printf("mouse : %d\t%d\t%d\n", x, y);
		doom->player.rot.y -= x / SENSIBILITY;
		return (0);
	}
	/* Moved in loop_hook because menu is now rendered everyframe
	if (doom->ui.curr_btn != curr_btn)
	{
		if ((curr_btn && (curr_btn->func || curr_btn->data)) || !curr_btn)
			draw_hover(doom, curr_btn, doom->ui.curr_btn);
		doom->ui.curr_btn = curr_btn;
	}
	*/
	if (doom->ui.currslid)
	{
		tmp = doom->ui.currslid;
		update_slider_value(doom, tmp, x);
	}
	return (0);
}
