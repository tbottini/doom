/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:57:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/12 10:59:21 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "debug.h"

t_fvct2			player_enemy_diff_heigth(t_player *player, t_enemy *enemy)
{
	t_fvct2		length;

	//on recupere la hauteur du personnage
	//on fait la difference avec le sol sur lequel il est et sa position par rapport au sol
	//la difference au sol avec l'enemy est la meme que la difference avec le sol ou l'enemy est
	length.y = -player->stat.height - (player->stat.pos.z - enemy->stat.sector->h_floor);
	length.x = length.y + enemy->stat.height;
	return (length);
}

/*
**	on recupere la difference basse et haute d'un objet par rapport au joueur
**	avec la hauteur du secteur et celui de l'obj
*/
t_fvct2			player_diff_heigth(t_player *player, double sector_floor, double obj_heigth)
{
	t_fvct2		length;

	length.y = -player->stat.height - (player->stat.pos.z - sector_floor);
	length.x = length.y + obj_heigth;
	return (length);

}

int				camera_proj_heigth(t_camera *camera, t_sdl *sdl, t_player *player, double h_diff, double depth)
{
	double		wall_angle;
	int			px;
	double		player_angle;

	player_angle = (player->stat.rot.x - 90) * TO_RADIAN;
	wall_angle = atan2(h_diff, depth);
	px = sdl->size.y / 2 - tan(wall_angle) * camera->d_screen;
	px += (player->stat.rot.x - 90) * 15.5;
	return (px);
}

t_vct2			player_prop_heigth_surface(t_arch *arch, t_player *player, t_prop *prop, double depth)
{
	t_fvct2		len;
	t_vct2		surface;

	len = player_diff_heigth(player, prop->sector->h_floor, 1);
	surface.x = camera_proj_heigth(arch->cam, arch->sdl, player, len.x, depth);
	surface.y = camera_proj_heigth(arch->cam, arch->sdl, player, len.y, depth);
	return (surface);
}

/*
**	on recupere la surface que l'enemy
**	prend verticalement sur une colonne de pixel selon ca profondeur
*/
t_vct2			cam_get_enemy_surface(t_camera *camera, t_sdl *sdl, t_enemy *enemy, t_player *player, double depth)
{
	t_fvct2		len;
	t_vct2		surface;

	len = player_enemy_diff_heigth(player, enemy);
	surface.x = camera_proj_heigth(camera, sdl, player, len.x, depth);
	surface.y = camera_proj_heigth(camera, sdl, player, len.y, depth);
	return (surface);
}

/*
**	on recupere la largeur de la texture a l'ecran a partir de ses dimensions de base et de
**	sa hauteur a l'ecran
**	on ajoute sa position x, colonne du millieu de texture
*/
t_vct2			txtr_width(t_txtr *texture, t_vct2 surface, int posx)
{
	//calcul en croix de la longeur en pixel
	t_vct2		width;

	width.x = (((surface.y - surface.x) / (double)texture->h) * texture->w) / 2;
	width.y = posx + width.x;
	width.x = posx - width.x;
	return (width);
}

void			draw_enemy_box(t_arch *arch, t_enemy *enemy, t_vct2 width, t_vct2 heigth, double neutral_distance)
{
	double		p_buff_h;
	double		p_buff_w;

	double		start_txtr_heigth;

	double		buffer_h;
	double		buffer_w;

	int			i_heigth;
	int			limit_h;
	int			cursor_screen;

	p_buff_h = (double)enemy->sprites.h / (double)(heigth.y - heigth.x);
	p_buff_w = enemy->sprites.w / (double)(width.y - width.x);

	//printf("prinp_buff_h %f\n", p_buff_h);

	if (heigth.x < 0)
	{
		heigth.x = 0;
		start_txtr_heigth = -heigth.x * p_buff_h;
	}
	else
	{
		start_txtr_heigth = 0;
	}
	if (width.x < 0)
	{
		buffer_w = -width.x * p_buff_w;
		width.x = 0;
	}
	else
	{
		buffer_w = 0;
	}

	if (width.y > arch->sdl->size.x)
		width.y = arch->sdl->size.x;
	if (heigth.y > arch->sdl->size.y)
		heigth.y = arch->sdl->size.y - 1;

	while (width.x < width.y)
	{
		if (zline_compare(arch, neutral_distance, width.x))
		{
			if (heigth.x < (int)arch->portal.b_up[width.x])
			{
				i_heigth = (int)arch->portal.b_up[width.x];
				buffer_h = (arch->portal.b_up[width.x] - heigth.x) * p_buff_h;
			}
			else
			{
				i_heigth = heigth.x;
				buffer_h = 0;
			}
			cursor_screen = width.x + (i_heigth * arch->sdl->size.x);
			if (heigth.y > (int)arch->portal.b_down[width.x])
				limit_h = arch->portal.b_down[width.x] * arch->sdl->size.x;
			else
				limit_h = heigth.y * arch->sdl->size.x;


			while (cursor_screen < limit_h)
			{
				arch->sdl->screen[cursor_screen] =
					enemy->sprites.pixels[(int)buffer_w + (int)buffer_h * enemy->sprites.w];
				cursor_screen += arch->sdl->size.x;
				buffer_h += p_buff_h;
			}
		}
		width.x++;
		buffer_w += p_buff_w;
	}

}

void			render_sector_enemy(t_arch *arch, t_sector *sector, t_player *player)
{
	t_enemy		*enemy_node;
	double		e_angle;
	t_fvct2		dist_cam;
	int			posx;
	t_vct2		enemy_surface;
	t_vct2		enemy_width;
	double		neutral_distance;

	enemy_node = sector->enemys;


	if (!enemy_node && debug == 8)
		printf("no enemy\n");
	while (enemy_node)
	{
		enemy_node->sprites = sector->txtrsol;
		//printf("pos %f %f\n", enemy_node->stat.pos.x, enemy_node->stat.pos.y);
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&enemy_node->stat.pos, player->stat.rot.y);
		//printf("e_angle %f\n", e_angle);
		if (e_angle < 90 && e_angle > -90)
		{
			dist_cam.x = distance(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&enemy_node->stat.pos);
			dist_cam.y = dist_cam.x * sin(e_angle * TO_RADIAN);
			dist_cam.x = dist_cam.x * cos(e_angle * TO_RADIAN);


			neutral_distance = (double)(arch->sdl->size.y) / dist_cam.x;
			b_point_debug(dist_cam, RED);
			posx = arch->sdl->size.x / 2 - dist_cam.y / dist_cam.x * arch->cam->d_screen;
			arch->sdl->screen[posx + (arch->sdl->size.y / 2) * arch->sdl->size.x] = 0xffffffff;

			enemy_surface = cam_get_enemy_surface(arch->cam, arch->sdl, enemy_node, player, dist_cam.x);

			sdl_line(arch->sdl, (t_vct2){posx, enemy_surface.x}, (t_vct2){posx, enemy_surface.y}, BLUE_SOFT);
			enemy_width = txtr_width(&enemy_node->sprites, enemy_surface, posx);
			arch->sdl->screen[enemy_width.x + (arch->sdl->size.y / 2) * arch->sdl->size.x] = 0x00ffffff;
			sdl_line(arch->sdl, (t_vct2){enemy_width.x, arch->sdl->size.y / 2}, (t_vct2){enemy_width.y, arch->sdl->size.y / 2}, YELLOW);
			draw_enemy_box(arch, enemy_node, enemy_width, enemy_surface, neutral_distance);

		}
		enemy_node = enemy_node->next;
	}
}