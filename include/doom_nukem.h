/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/06/21 14:04:38 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "render.h"
# include "editor.h"
# include "editor.h"
# include "input.h"

# define MINWIDTH 800
# define MINHEIGHT 800
# define WIDTH 1920
# define HEIGHT 1080
# define MAXWIDTH 1920
# define MAXHEIGHT 1080
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131

/*
**	Color
*/
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff

# define ACCELERATION 8000.0
# define DECELERATION 2500.0
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"
# define MAX_FAR 10000
//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision
# define JOYSTICK_DEAD_ZONE 5000
# define SENSIBILITY 6.0

/*
** Editor Stuff
*/
#define MAXZOOM 20000
# define EDITORPRECISION 10000
# define DEBUG 0

/*
**	gestion
*/

void					updateText(SDL_Renderer *rend, TTF_Font *font, SDL_Texture **text, SDL_Rect *loc, const char *str, SDL_Color fg, SDL_Color bg);
void					dropfile_event(t_doom *doom, SDL_Event e);
void					doom_exit(t_doom *doom);
t_doom					*doom_init();
int						designer_init(t_designer *designer, t_sdl *sdl, t_camera *cam);
void					editor_free(t_editor *editor);
int						editor_init(t_editor *editor);
void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);
void					ui_free(t_ui *ui);
int						ui_init(t_ui *ui);
int						ui_by_sdl(t_doom *doom, t_ui *ui);

/*
**	parsing
*/

t_wall					*chunck_walls(t_list *chunck_line, t_designer *ressources, size_t len);
int						chunk_texture(t_sdl *sdl, t_designer *designer, int fd);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd, t_designer *ressources);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);

/*
**	debug
*/
void					move_input(t_doom *doom, int key);
void					mvt_input(t_player *player, int key);
void					move(t_stat *stat);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
void					draw_wall(t_designer *arch, t_player *player);
void					minimap(t_doom *d);
void					PrintEvent(const SDL_Event *event);
int						keyboard_input(t_doom *doom, SDL_Event event);
void					play_effect(t_sound *sound, int e);

/*
**	Cinematique et Musique
*/

void					prev_track(t_doom *doom);
void					next_track(t_doom *doom);
void					effect_free(t_sound *sound);
int						effect_init(t_sound *sound);
void					music_free(t_sound *sound);
int						music_init(t_sound *sound);
void					change_music(t_sound *sound, int n, int fade);
void					cinematrique(t_doom *doom);
void					effect_volume(t_sound *sound);

#endif
