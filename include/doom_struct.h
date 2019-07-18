#ifndef DOOM_STRUCT_H
# define DOOM_STRUCT_H

# include <fcntl.h>
# include <dirent.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <limits.h>
# include "sector.h"
# include "player.h"
# include "calcul.h"
# include "libft.h"


# define WIDTH 1300
# define HEIGHT 950


typedef struct s_doom	t_doom;
typedef struct s_enemy	t_enemy;
typedef struct s_sector	t_sector;
typedef struct s_wall	t_portal;
typedef struct s_prop	t_prop;

# define MAXTXTRNUMBER 500
# define MAXFILENAMELEN 20

# define MINENEMYPOS 1
# define MAXENEMYNUMBER 4
# define MAXENEMYPOS (MINENEMYPOS + MAXENEMYNUMBER)

# define MINPROPSPOS 20
# define MAXPROPSNUMBER 6
# define MAXPROPSPOS (MINPROPSPOS + MAXPROPSNUMBER)
# define PROPHEALTH "ressources/props/health.xpm"
# define PROPCASS "ressources/props/cassette.png"
# define PROPMUN "ressources/props/munition.xpm"
# define PROPRPILL "ressources/props/pill.png"
# define PROPGPILL "ressources/props/greenpill.png"
# define PROPBPILL "ressources/props/bluepill.png"

# define MINWPROPSPOS (MAXPROPSPOS + 1)
# define MAXWPROPSNUMBER 1
# define MAXWPROPSPOS (MINWPROPSPOS + MAXWPROPSNUMBER)
# define PROPBTN "ressources/props/button.ico"

# define ISENEMY(x) (MINENEMYPOS <= x && x < MAXENEMYPOS)
# define ISPROP(x) (MINPROPSPOS <= x && x < MAXPROPSPOS)
# define ISWALLPROP(x) (MINWPROPSPOS <= x && x < MAXWPROPSPOS)
# define ISPORTAL(x) (x >= OPEN_DOOR)

enum 					e_window_id
{
	DOOM_WINDOW = 1,
	EDITOR_WINDOW = 2
};

typedef struct s_entity	t_entity;
typedef t_entity			*t_lstent;

typedef struct s_mur	t_mur;
typedef t_mur			*t_lstmur;

typedef struct s_secteur	t_secteur;
typedef t_secteur		*t_lstsec;

typedef struct			s_slen
{
	int	nb_pills;
	int	nb_txtrs;
	int	nb_sects;
}						t_slen;

/*
** editor coord on map
*/
typedef struct 			s_ecoord
{
	t_secteur			*sector; // Linked Sector
	t_mur				*mur; // Linked Wall
	t_secteur			*mursec; // Linked Wall sector
	t_vct2				pos;
	int					type; // Health if player
	double				roty;
}						t_ecoord;

typedef struct			s_eplayer
{
	t_ecoord			stat;
}						t_eplayer;

struct					s_entity
{
	t_ecoord			stat;
	t_entity			*next;
	t_entity			*prev;
};

/*
** Snap var behaviour
** 0 = center of object is its left;
** 1 = center of object is its center;
** 2 = center of object is its right;
** 3 = under the object before + (pos) px
** 4 = center of the object before + (pos) px
** 5 = over the object before + (pos) px
*/
typedef struct			s_sloc
{
	SDL_Rect			area;
	SDL_Rect			*parent;
	int					snapx;
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
	Uint32				*screen;
	t_vct2				*size;
}						t_pal;

/*
** 0 : pills
** 1 : cassette
** 2 : Health Pack
** 3 : Munition Pack
** 4 : Button
*/

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
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	Uint32				*screen;
	t_tab				keys;
	Uint32				timp; // A Supprimer lorqu'il n'y aura plus besoin d'afficher les FPS
	int					fps;
}						t_sdl;

typedef struct			s_minimap
{
	t_vct2	d;
	t_vct2	a;
	t_vct2	size;
	t_vct2	mid;
	t_sdl	*sdl;
}						t_minimap;

typedef struct s_pilier	t_pilier;
typedef t_pilier		*t_lstpil;

struct					s_pilier {
	int					id;
	t_vct2				pos;

	t_lstpil			prvs;
	t_lstpil			next;
};

struct					s_mur {
	t_pilier			*pil1;
	t_pilier			*pil2;
	SDL_Texture			*txtr;
	int					idtxtr;
	t_secteur			*portal_ptr;
	t_portal_id			portal_id;
	t_lstent			wproplist;
	t_lstmur			prvs;
	t_lstmur			next;
	int					id;
};

struct					s_secteur
{
	int					id;
	t_lstmur			murs;
	SDL_Texture			*top;
	int					idtop;
	SDL_Texture			*sol;
	int					idsol;
	int					hsol; // Hauteur du sol par rapport a 0
	int					htop; // Hauteur du plafond par rapport au sol
	char				gravity; // 0 : gravite Lunaire 🌝 | 1 : Gravite Terrestre 🌍
	t_lstsec			prvs;
	t_lstsec			next;
};

/*
** selecttxtr 1 fill obvious
** selecttxtr 2 remplir sol de secteur
** selecttxtr 3 remplir type de props
*/
typedef enum		e_selecttxtr
{
	NOSELECT,
	FILL_TXTR,
	FILL_SOL,
	FILL_PROP,
	FILL_WPROP
}					t_selecttxtr;

/*
** 0 : Window is closed
** 1 : Textures are loading
** 2 : Textures are loaded
*/
typedef enum		e_editorstatus
{
	ED_CLOSED,
	ED_LOADING,
	ED_LOADED,
	ED_WRITING,
	ED_SAVING
}					t_editorstatus;

typedef struct			s_editor
{
	t_editorstatus		status;
	t_selecttxtr		selecttxtr;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_ui				*ui;
	t_vct2				size;
	t_vct2				mouse; //Mouse pos
	t_vct2				mapmouse;
	int					sectscroll; // Current scroll of sector menu
	int					txtrscroll; // Current scroll of texture menu
	SDL_Rect			sectbox;
	SDL_Rect			optbox;
	SDL_Rect			txtrbox;
	t_tab				keys;
	t_pilier			*currpilier;
	t_ecoord			*currstat;
	t_mur				*currmur;
	int					*currwriter;
	t_pilier			*hoverpilier;
	t_mur				*hovermur;
	t_lstsec			map;
	t_vct3				mappos;
	t_eplayer			player; // [map] donnees sur le player
	t_lstpil			pillist; // [map] Liste de pilliers
	t_lstent			ennlist; // [map] Liste d'ennemis
	t_lstsec			sectors;  // [map] Liste des secteurs (contenant les murs)
	//int					*idtoeditor; // Used when opening file to editor (Abandon)
	SDL_Texture			*txtrgame[MAXTXTRNUMBER]; // [map] Contient le pointeur a verif pour avoir l'ID de la texture du mur
	SDL_Texture			*txtrreal[MAXTXTRNUMBER]; // [map] Used when saving map
	SDL_Texture			*sprites[MAXPROPSNUMBER]; // [map] Contient le pointeur a verif pour avoir l'ID du prop
	SDL_Texture			*wsprites[MAXWPROPSNUMBER]; // [map] Contient le pointeur a verif pour avoir l'ID du wallprop
	char				*txtrname[MAXTXTRNUMBER]; // [map] Contient le path de la texture
	char				filename[MAXFILENAMELEN]; // Truc que Thomas voulait
}						t_editor;

typedef struct 			s_camera
{
	int					fov;
	double				d_screen;
}						t_camera;


/*
**	structure principale pour la recursivite
*/
typedef struct 			s_borne
{
	double				*zline;
	uint32_t			*b_down;
	uint32_t			*b_up;
	double				b_left;
	double				b_right;
	t_fvct2				decal_portal;
	t_fvct2				depth_portal;
}						t_borne;

typedef struct 			s_arch
{
	t_sector			*sector;
	t_wall				*wall;
	t_camera			*cam;
	t_sdl				*sdl;
	SDL_Surface			**texture;
	uint16_t			depth_portal;
	t_fvct2				depth;
	t_fvct2				decal;
	t_vct2				px;
	t_fvct2				shift_txtr;
	t_borne				bound;

	//debug
	Uint32			sc_debug[WIDTH * HEIGHT];
}						t_arch;

typedef enum		e_difficulty
{
	EASY,
	MEDIUM,
	HARD
}					t_difficulty;

typedef struct			s_game
{
	t_slen				len;
	t_player			player;
	t_sound				sound;
	t_sector			*sectors;
	t_pillar			*pillars;//
	SDL_Surface			**gamesurf;//
	t_arch				arch;//a voir aveec tbottini
	t_camera			camera;//
	t_difficulty		difficulty;
}						t_game;

struct					s_doom
{
	int					debug;
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	Uint32				timestamp;
	SDL_GameController	*controller;
	t_game				game;
};

#endif
