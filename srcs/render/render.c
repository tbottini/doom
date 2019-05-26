#include "doom_nukem.h"


int					doom_render(t_doom *doom)
{
	portal_engine(doom);
	minimap(doom);
	sdl_present(&doom->sdl);
	return (1);
}
