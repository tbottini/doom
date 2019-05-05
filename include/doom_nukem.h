
#ifndef DOOM_NUKEM
# define DOOM_NUKEM

# include "doom.h"

//portal engine

typedef	uint32_t* t_texture;

//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision

typedef struct 			s_wl
{
	t_fvct2				pos;
	struct s_wl			*next;
	t_texture			*t_wall;
	float				angle;
	char				frust;
}						t_wl;

typedef	struct 			s_ssector
{
	t_fvct2				*root_wall;
	int					len;
	t_texture			t_ceil;
	t_texture			t_floor;
	float				h_ceil;
	float				h_floor;
}						t_ssector;

typedef	struct 			s_sector
{
	t_wl				*root_wall;
	int					len;
	t_texture			t_floor;
	t_texture			t_ceil;
	float				h_ceil;
	float				h_floor;
}						t_sector;

typedef struct 			s_player
{
	t_fvct2				pos;
	t_fvct2				rot;
	int					fov;
	t_fvct2				vel;
	float				d_scrn;
}						t_player;

typedef	struct			s_doom
{
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	unsigned long		timestamp;
	SDL_GameController *controller;
	t_player			player;
	t_sector			*sector;
}						t_doom;

float					ft_atof(char *str);
float					ft_catof(char *str, char c);
int						parsing(t_doom *doom, char *filename);
void					fvct2_print(t_fvct2 vct);
void					sector_describe(t_sector sector);
void					portal_engine(t_doom *doom);
void					fvct2_msg(char *msg, t_fvct2 vct);
void					describe_bunch(t_wl **bunch);
t_fvct2					wall_clipping(t_wl wall, t_fvct2 origin, float ang);

t_doom					*doom_init();
void					*sdldata_quit(t_sdl **data);
int						sdl_start(t_doom *doom, const char *title);
void					sdl_showscreen(t_sdl *sdl);
int						doom_parseur(t_doom *doom, char *filename);
int						prog_quit(t_doom *doom);
void					btn_click(t_doom *doom, int x, int y);
t_btn					add_start_button(t_doom *doom);
t_btn					add_mapmenu_button(t_doom *doom);
t_btn					add_map_button(t_doom *doom, const char *str);
t_btn					add_doom_button(t_doom *doom);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_editor_button(t_doom *doom);
t_btn					add_quit_button(t_doom *doom, const char *str);
int						sdl_set_status(t_doom *doom, int status);
void					draw_menu(t_doom *doom);
int						load_map_btns(t_doom *doom);
void					update_loc(t_doom *doom, t_sloc *loc, t_sloc before);
void					update_slider_txt(t_doom *doom, t_slid *slid);
t_slid					add_fov_slider(t_doom *doom);
void					draw_slid(t_doom *doom, t_slid *tmp);
int						event_handler(t_doom *doom);
int						event_handler1(t_doom *doom, SDL_Event event);
int						event_handler2(t_doom *doom, SDL_Event event);
int						loop_hook(t_doom *doom);
t_btn					*btn_hover(t_doom *doom, int x, int y);
void					draw_hover(t_doom *doom, t_btn *new, t_btn *old);
void					move(t_doom *doom, int x, int y);
int						key_press(int key, t_doom *doom);
int						key_release(int key, t_doom *doom);
int						mouse_press(int button, int x, int y, t_doom *doom);
int						mouse_release(int button, int x, int y, t_doom *doom);
int						mouse_move(int x, int y, t_doom *doom);
void					raycasting(t_doom *doom);
double					double_modulo(double num);
double					angle_adaptater(double angle);
void					print_image(SDL_Surface *png);
float					ver_detection(t_doom *doom, t_ray *ray);
float					hor_detection(t_doom *doom, t_ray *ray);
double					iswall(t_doom *doom, t_fvct2 inter);
void					draw_column(t_doom *doom, t_ray ray, int num);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					doom_clear_map(t_doom *doom);
int						map_check(t_doom *doom, char *filename);
int						row_verif(t_doom *doom, char *row);
void					*listdel(t_list **list);
t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);
char					**tab_new(int y);
void					controller_handler(t_doom *doom, SDL_Event event);
void					lst_del_node(t_list **node);
int						start_editor(t_doom *doom);
int						close_editor(t_doom *doom);

int						secure_doom(t_doom *doom);

void					debug_player(t_player player);


/*
**	gestion
*/
void					doom_exit(t_doom *doom);
t_doom					*doom_init();
void					editor_free(t_editor *editor);
int						editor_init(t_editor *editor);
void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);
void					ui_free(t_ui *ui);
int						ui_init(t_ui *ui);
int						ui_by_sdl(t_ui *ui, t_doom *doom);

/*
**	simple input
*/
int						keyboard_input(t_doom *doom, SDL_Event event);

void					PrintEvent(const SDL_Event *event);
void					debug_up(t_doom *doom);
void	sdl_present(t_sdl *sdl);

void		point_gras(t_vct2 cursor, uint32_t color, t_doom *doom);
void			trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, uint32_t col);
#endif
