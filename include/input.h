#ifndef INPUT_H
# define INPUT_H
#include "doom_struct.h"

/*
** End Button Functions
*/

int						parsing(t_doom *doom, char *filename);

void					fire_init(t_doom *doom);
void					fire(t_pal *fire);
void					fire_on_off(Uint32 *screen, t_vct2 size, int status);

void					btn_click(t_doom *doom, int x, int y);
t_btn					add_start_button(t_doom *doom);
t_btn					add_mapmenu_button(t_doom *doom);
t_btn					add_map_button(t_doom *doom, const char *str);
t_btn					add_pause_button(t_doom *doom);

t_btn					add_left_music_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_middle_music_button(t_doom *doom);
t_btn					add_right_music_button(t_doom *doom, SDL_Rect *parent);

t_btn					add_left_difficulty_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_middle_difficulty_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_right_difficulty_button(t_doom *doom, SDL_Rect *parent);


t_btn					add_resume_button(t_doom *doom);
t_btn					add_doom_button(t_doom *doom, const char *name);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_ing_opt_button(t_doom *doom);
t_btn					add_main_menu_button(t_doom *doom);
t_btn					add_editor_button(t_doom *doom);
t_btn					add_quit_button(t_doom *doom, const char *str,
																void *fc);
int						sdl_set_status(t_doom *doom, int status);
void					draw_menu(t_doom *doom);
int						load_map_btns(t_doom *doom);
void					update_loc(t_vct2 size, t_sloc *loc, SDL_Rect before);
void					update_slider_txt(t_doom *doom, t_slid *slid);
void					update_slider_value(t_doom *doom, t_slid *slid, int v);
t_slid					add_fov_slider(t_doom *doom);
t_slid					add_music_slider(t_doom *doom);
t_slid					add_effect_slider(t_doom *doom);
void					draw_slid(t_doom *doom, t_slid *tmp);

int						event_handler(t_doom *doom);
int						event_handler_doom(t_doom *doom, SDL_Event event);
int						event_handler_editor(t_doom *doom, SDL_Event event);

int						loop_hook(t_doom *doom);
t_btn					*btn_hover(t_doom *doom, int x, int y);
void					draw_hover(t_doom *doom, t_btn *newl, t_btn *old);

int						key_press(int key, t_doom *doom);
int						key_release(int key, t_doom *doom);
int						mouse_press(int button, int x, int y, t_doom *doom);
int						mouse_release(int button, int x, int y, t_doom *doom);
int						mouse_move(int x, int y, t_doom *doom);

double					double_modulo(double num);
double					angle_adaptater(double angle);
void					print_image(SDL_Surface *png);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					*listdel(t_list **list);

char					**tab_new(int y);
void					controller_handler(t_doom *doom, t_player *player, SDL_Event event);
void					lst_del_node(t_list **node);
void					open_editor(t_doom *doom);
int						close_editor(t_doom *doom);
int						secure_doom(t_doom *doom);

/*
** Button Functions
*/

void					start_button(t_doom *doom);
void					resume_button(t_doom *doom);
void					start_map_button(t_doom *doom);
void					option_button(t_doom *doom);
void					ignoption_button(t_doom *doom);
void					main_menu_button(t_doom *doom);
void					return_button(t_doom *doom);

void					set_easy(t_doom *doom);
void					set_medium(t_doom *doom);
void					set_hard(t_doom *doom);

/*
**	simple input
*/

void					bullet(t_stat *stat);
void					action(t_player *player, t_stat *stat);
void					kick(t_doom *doom, t_player *player);
void					PrintEvent(const SDL_Event *event);
void					debug_up(t_doom *doom);
void					sdl_MultiRenderCopy(t_sdl *sdl);
void					calcdelay(const char *str, t_doom *doom);
int						pos_in_rect(SDL_Rect rect, int x, int y);

void					point_gras(t_vct2 cursor, Uint32 color, t_doom *doom);
void					trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, Uint32 col);
double					distance(t_fvct2 vct1, t_fvct2 vct2);
t_wall					*collision(t_sector *sector, t_fvct3 pos, t_wall *w);
t_wall					*collisionV21(t_sector *sector, t_fvct3 ori, t_fvct3 pos, t_wall *w);
int						colli_teleport(t_stat *stat, t_sector *sector, t_fvct3 ori, t_fvct3 pos);
int						vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2);
void					bulletV42(t_doom *doom, t_player *player);

#endif
