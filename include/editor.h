#ifndef EDITOR_H
# define EDITOR_H

#include "doom_struct.h"

/*
** Editor
*/

int						write_hook(t_doom *doom, char *str, SDL_KeyboardEvent e);
void					draw_writer(t_editor *edit);

int						save_editor_to_file(t_editor *edit);

t_btn					add_test_button(t_editor *edit, SDL_Rect *parent);

void					editor_zoom(int *z, int zoom);

int						editor_key_press(int key, t_doom *doom);
int						editor_key_release(int key, t_doom *doom);
int						editor_mouse_press(SDL_MouseButtonEvent e, t_editor *edit);
int						editor_mouse_release(int button, int x, int y,
																t_doom *doom);
int						editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit);
int						editor_mouse_wheel(SDL_MouseWheelEvent e, t_editor *edit);

t_vct2					get_rel_mappos(t_editor *editor, int x, int y);

void					draw_map(t_editor *editor);
void					draw_sector_menu(t_editor *editor, t_font font);
void					draw_inspect_menu(t_editor *editor);

void					sector_menu(t_editor *edit, int pos, int del);
int						ft_walllen(t_lstmur start);
void					ft_remove_walls_with_pillar(t_lstmur *start, t_pilier *pil);
void					ft_removewall(t_lstmur *start, t_mur **mur);
void					ft_movewall(t_mur *wall, int addx, int addy, int zoom);
t_lstmur 				ft_wallpushend(t_lstmur *start, t_pilier *pil1, t_pilier *pil2, SDL_Texture *txtr);
void					ft_clear_wall_list(t_lstmur *start);
t_secteur				*sector_menu_click(t_editor *edit, int pos, int cas);
int						opt_menu_click(t_editor *edit, int pos);
int						opt_menu_wheel(SDL_MouseWheelEvent e, t_editor *edit);
SDL_Texture				*txtr_menu_click(t_editor *edit, int x, int y, int max);
int						txtr_menu_click_int(t_editor *editor, int x, int y, int min, int max);
void					texturebox_click(t_editor *edit, SDL_MouseButtonEvent e);
t_mur					*find_mur(t_editor *editor, t_lstsec start, int x, int y);
t_lstpil				ft_newpillar(t_vct2 loc);
void					ft_movepillar(t_lstsec sectors, t_pilier *pil, int addx, int addy, int zoom);
void					ft_removepillar(t_lstpil *start, t_lstpil *pil);
t_lstpil				ft_pillarpushend(t_lstpil *start, t_vct2 loc);
void					ft_clear_pillar_list(t_lstpil *start);
void					ft_nodeprint_pillar(t_lstpil node);
void 					ft_nodeprint_secteur(t_lstsec node);
t_lstpil				find_pilier(t_editor *editor, t_lstpil start, int x, int y);
t_ecoord				*find_player(t_editor *edit, int x, int y);

int						add_pillar(t_editor *edit, int x, int y);

t_lstsec				ft_newsector(SDL_Texture *top, SDL_Texture *sol);
t_lstsec				push_secteur(t_lstsec *node, SDL_Texture *top, SDL_Texture *sol);
void					ft_remove_pillar_from_sector(t_lstsec sectors, t_lstpil *start, t_lstpil *pil);
void					ft_clear_secteur(t_lstsec *sec);
void					ft_clear_secteur_list(t_lstsec *start);

t_entity					*ft_newenemy(t_vct2 loc, int type, t_secteur *sctr);
void					ft_removeenemy(t_lstent *start, t_entity **pil);
t_entity					*ft_enemypushend(t_lstent *start, t_vct2 loc, int type, t_secteur *sctr);
void					ft_removeenemywithstat(t_lstent *start, t_ecoord **pil);
void					ft_nodeprint_enemy(t_lstent node);
void					ft_clear_entity_list(t_lstent *start);

t_vct2					line_percent(t_vct2 pos1, t_vct2 pos2, double percent);

t_vct2					get_screen_mappos(t_editor *editor, int x, int y);
t_vct2					get_rel_mappos(t_editor *editor, int x, int y);

/*
**	editor_manager
*/
int						editor_reset(t_editor *editor);

#endif
