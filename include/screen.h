
#ifndef SCREEN_H
# define SCREEN_H

# define WIDTH 1280
# define HEIGHT 720

# define MINWIDTH 1024
# define MINHEIGHT 576
# define MAXWIDTH 1920
# define MAXHEIGHT 1080

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	Uint32				*screen;
	t_tab				keys;
	Uint32				timp; // A Supprimer lorqu'il n'y aura plus besoin d'afficher les FPS
	int					fps;
}						t_sdl;

/*
**	fov: le fov horizontal de la camera (en degre)
**	fov_ver : le fov vertical (en radian)
*/
typedef struct 			s_camera
{
	int					fov;
	double				fov_ver;
	double				d_screen;
}						t_camera;

typedef struct 			s_screen
{
	uint32_t			*screen;
	int					w;
	int					h;
}						t_screen;


void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);

t_camera				*camera_init(t_camera *camera, t_sdl *sdl, int fov);

void					fill_line(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color);
void					trait(t_screen *screen, t_vct2 vct1, t_vct2 vct2, Uint32 col);
void					sdl_multirendercopy(t_sdl *sdl);

typedef struct			s_sp
{
	SDL_Renderer		*rend;
	TTF_Font			*font;
	t_vct2				loc;
	const char			*text;
	SDL_Color			fg;
}						t_sp;

int						sdl_string_put(t_sp norm);

typedef struct			s_ip
{
	SDL_Renderer		*rend;
	TTF_Font			*font;
	t_vct2				loc;
	const char			*label;
	const int			value;
	SDL_Color			fg;
}						t_ip;

int						sdl_int_put(t_ip norm);
void					sdl_line(t_sdl *sdl, t_vct2 a, t_vct2 b, uint32_t color);

#endif
