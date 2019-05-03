/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/05/03 13:07:09 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void PrintEvent(const SDL_Event *event)
{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_Log("Window %d exposed", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Window %d moved to %d,%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Log("Window %d resized to %dx%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Window %d size changed to %dx%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Window %d minimized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Window %d maximized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Window %d restored", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Mouse entered window %d",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Mouse left window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Window %d gained keyboard focus",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Window %d lost keyboard focus",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Window %d closed", event->window.windowID);
			break;
		default:
			SDL_Log("Window %d got unknown event %d",
					event->window.windowID, event->window.event);
			break;
		}
}

//<<<<<<< HEAD
//static void		window_event(t_doom *doom, SDL_Event event)
//{
//	void	*tmp;
//	int		pitch;
//
//	//PrintEvent(&event);
//	SDL_GetWindowSize(doom->sdl.win, &(doom->sdl.size.x), &(doom->sdl.size.y));
//	if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
//		|| event.window.event == SDL_WINDOWEVENT_RESIZED)
//	{
//		if (doom->sdl.txture)
//			SDL_DestroyTexture(doom->sdl.txture);
//		doom->sdl.txture = SDL_CreateTexture(doom->sdl.rend,
//			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
//			doom->sdl.size.x, doom->sdl.size.y);
//		if (SDL_LockTexture(doom->sdl.txture, NULL, &tmp, &pitch))
//			prog_quit(doom);
//		doom->sdl.screen = (uint32_t *)tmp;
//		draw_menu(doom);
//	}
//	if (doom->ui.m_status == 2)
//	{
//		load_map_btns(doom);
//		draw_menu(doom);
//	}
//}
//
//static void		dropfile_event(t_doom *doom, SDL_Event event)
//{
//	if (doom->map)
//		doom_clear_map(doom);
//	if (doom_parseur(doom, event.drop.file))
//	{
//		doom->ui.m_status = 0;
//	}
//	else
//	{
//		ft_printf("Error Reading File Drop\n");
//		doom->ui.m_status = 1;
//		draw_menu(doom);
//	}
//	SDL_free(event.drop.file);
//}
//
//void			lil_event_handler(t_doom *doom, SDL_Event event)
//{
//	if (event.type == SDL_MOUSEMOTION)
//		mouse_move(event.motion.x, event.motion.y, doom);
//	else if (event.type == SDL_MOUSEBUTTONDOWN)
//		mouse_press(event.button.button,
//			event.button.x, event.button.y, doom);
//	else if (event.type == SDL_MOUSEBUTTONUP)
//		mouse_release(event.button.button,
//			event.button.x, event.button.y, doom);
//	else if (event.type == SDL_MOUSEWHEEL)
//		mouse_press((event.wheel.y > 0 ? 4 : 5),
//			doom->sdl.m_pos.x, doom->sdl.m_pos.y, doom);
//}
//
//=======
//>>>>>>> ba2b44c8345292dc33dcac0bb42d29312e70f85c
int				event_handler(t_doom *doom)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.window.windowID == 1)
			event_handler1(doom, event);
		else if (event.window.windowID == 2)
			event_handler2(doom, event);
		if (event.type == SDL_CONTROLLERDEVICEADDED)
		{
			ft_printf("Controller Added\n");
			doom->controller = SDL_GameControllerOpen(0);
		}
		else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			ft_printf("Controller Removed\n");
		}
		else if (event.type == SDL_CONTROLLERAXISMOTION || event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
			controller_handler(doom, event);
		else
		{
			//ft_printf("Event %d\n", event.type);
		}
	}
	return (1);
}
