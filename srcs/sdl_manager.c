#include "wolf3d.h"

void PrintEvent(const SDL_Event *event)
{
	if (event->type == SDL_WINDOWEVENT)
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
}

int sdl_start(t_wolf *wolf, const char *title)
{
	void	*tmp;
	int		pitch;

	wolf->sdl.size.x = WIDTH;
	wolf->sdl.size.y = HEIGHT;
	wolf->sdl.m_status = 1;
	if (!(wolf->sdl.win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)))
		return (prog_quit(wolf));
	if (!(wolf->sdl.rend = SDL_CreateRenderer(wolf->sdl.win, -1, SDL_RENDERER_SOFTWARE)))
		return (prog_quit(wolf));
	if (!(wolf->sdl.fonts.s64 = TTF_OpenFont("wolfenstein.ttf", 64)))
		return (prog_quit(wolf));
	if (!(wolf->sdl.fonts.s128 = TTF_OpenFont("wolfenstein.ttf", 128)))
		return (prog_quit(wolf));
	if (!(wolf->sdl.fonts.s32 = TTF_OpenFont("impact.ttf", 32)))
		return (prog_quit(wolf));
	SDL_SetWindowMinimumSize(wolf->sdl.win, 640, 480);
	wolf->sdl.txture = SDL_CreateTexture(wolf->sdl.rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(wolf->sdl.txture, NULL, &tmp, &pitch))
		return (prog_quit(wolf));
	wolf->sdl.screen = (uint32_t*)tmp;
	return (0);
}
