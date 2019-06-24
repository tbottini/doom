#ifndef DOOM_STRUCT
# define DOOM_STRUCT

typedef struct s_doom	t_doom;
typedef double	t_zline;
typedef uint32_t	t_texture;
/*
** Snap var behaviour
** 0 = center of object is its left;
** 1 = center of object is its center;
** 2 = center of object is its right;
** 3 = under the object before + (pos) px
** 4 = center of the object before + (pos) px
** 5 = over the object before + (pos) px
*/

enum 					e_window_id
{
	DOOM_WINDOW = 1,
	EDITOR_WINDOW = 2
};

typedef struct			s_sloc
{
	SDL_Rect			area;
	int					snapx;
	struct s_sloc		*parent;
	int					snapy;
	t_vct2				pos;
}						t_sloc;

typedef struct			s_btn
{
	t_sloc				loc;
	SDL_Texture			*txture;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
	char				*data;
	SDL_PixelFormat		*format;
	void				(*func)(t_doom *doom);
}						t_btn;

typedef struct			s_slid
{
	t_sloc				loc;
	SDL_Texture			*txture;
	SDL_Texture			*label;
	int					*val;
	int					min;
	int					max;
	SDL_Rect			grip;
	SDL_Rect			griplabel;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
}						t_slid;

typedef struct			s_sound
{
	Mix_Chunk			*e_world;
	Mix_Chunk			*e_perso;
	Mix_Chunk			*e_other;
	Mix_Chunk			*tab_effect[50];//changer nb effects
	Mix_Music			*music;
	Mix_Music			*tab_music[11];
	int					on;
	int					maxmusic;
	int					musicvolume;
	int					effectvolume;
}						t_sound;

typedef struct			s_font
{
	TTF_Font			*s32;
	TTF_Font			*s64;
	TTF_Font			*s128;
}						t_font;

/*
** m_status behaviour
** 0 = gamemode
** 1 = Show main menu
** 2 = show map menu
** 3 = Pause menu
*/

typedef struct			s_pal {
	Uint32				pal[38];
	int					height;
}						t_pal;

typedef struct			s_ui
{
	t_font				fonts;
	t_btn				btnarr[20];
	t_btn				btnmap[20];
	t_btn				btnopt[20];
	t_btn				btnpse[20];
	t_slid				slidopt[10];
	t_slid				*currslid;
	int					m_status;
	t_btn				*curr_btn;
	int					curr_btn_controller;
	t_pal				fire;
}						t_ui;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Window			*edwin;
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	Uint32				*screen;
	t_tab				keys;
	SDL_PixelFormat		*format;
	Uint32				timp; // A Supprimer lorqu'il n'y aura plus besoin d'afficher les FPS
	int					fps;
}						t_sdl;

typedef struct s_pilier	t_pilier;
typedef t_pilier		*t_lstpil;

struct					s_pilier {
	t_vct2				pos;

	t_lstpil			prvs;
	t_lstpil			next;
};

typedef struct s_mur	t_mur;
typedef t_mur			*t_lstmur;

struct					s_mur {
	t_pilier			*pil1;
	t_pilier			*pil2;

	t_lstmur			prvs;
	t_lstmur			next;
};

typedef struct s_secteur	t_secteur;
typedef t_secteur		*t_lstsec;

struct					s_secteur {
	t_lstmur			murs;

	t_lstsec			prvs;
	t_lstsec			next;
};

typedef struct			s_editor
{
	int					status;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_btn				btnarr[20];
	t_vct2				size;
	t_vct2				mouse; //Mouse pos
	t_vct2				mapmouse;
	int					sectscroll; // Current scroll of sector menu
	SDL_Rect			sectbox;
	//SDL_Texture			*txture;
	//Uint32				*screen;
	t_tab				keys;
	t_lstpil			pillist;
	t_pilier			*currpilier;
	t_pilier			*hoverpilier;
	t_mur				*currmur;
	t_mur				*hovermur;
	t_lstsec			sectors; // list of all root pillards in sector
	t_lstsec			map;
	t_vct3				mappos;
}						t_editor;

typedef struct 			s_camera
{
	int					fov;
	double				d_screen;
}						t_camera;

typedef struct 			s_designer
{
	uint32_t			*bot[1920];
	uint32_t			*top[1920];
	t_sector			*sector;
	t_wall				*wall;
	t_camera			*cam;
	t_sdl				*sdl;
	SDL_Surface			**texture;
	t_fvct2				depth;
	t_fvct2				decal;
	t_vct2				px;
	t_fvct2				shift_txtr;
	double				*zline;
	//double			coef_px;
}						t_designer;

struct					s_doom
{
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	Uint32				timestamp;
	t_player			player;
	t_sound				sound;
	SDL_GameController	*controller;
	t_sector			*sector;			//root sector
	t_vct2				vel;
	t_designer			tool;
	t_camera			camera;
};

#endif
