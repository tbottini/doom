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

t_vct2			cam_enemy_width(t_camera *camera, t_enemy *enemy, t_vct2 surface, int posx)
{
	//calcul en croix de la longeur en pixel
	t_vct2		width;

	width.x = (((surface.y - surface.x) / (double)enemy->sprites->h) * enemy->sprites->w) / 2;
	width.y = posx + width.x;
	width.x = posx - width.x;
	return (width);
}

/*
void			draw_enemy_box(t_arch->sdl *arch->sdl, t_enemy *enemy, t_vct2 width, t_vct2 heigth)
{
	double		buff_h;
	double		buff_w;
	t_vct2		cursor_screen;
	t_vct2		cursor_txtr;
	t_fvct2		buff_cursor;
	double		start_x_txtr;
	int			cursor_s;
	int			cursor_t;

	int			limit_h, limit_w;

	buff_h = enemy->sprites->h / (double)(heigth.y - heigth.x);
	buff_w = enemy->sprites->w / (double)(width.y - width.x);

	buff_cursor = (t_fvct2){0, 0};


	cursor_txtr.x = (int)buff_cursor.x;
	cursor_txtr.y = (int)buff_cursor.y;

	if (width.x < 0)
	{
		start_x_txtr = -width.x * buff_w;
		buff_cursor.x = start_x_txtr;
		width.x = 0;
		cursor_screen.x = 0;
	}
	else
	{
		cursor_screen.x = width.x;
	}
	if (heigth.x < 0)
	{
		buff_cursor.y = -heigth.x * buff_h;
		cursor_screen.y = 0;
	}
	else
	{
		cursor_screen.y = heigth.x * arch->sdl->size.x;
	}
	if (heigth.y > arch->sdl->size.y)
		heigth.y = arch->sdl->size.y * arch->sdl->size.x;
	else
		heigth.y *= arch->sdl->size.x;
	if (width.y > arch->sdl->size.x)
		width.y = arch->sdl->size.x;

	limit_h = heigth.y - arch->sdl->size.x;

	cursor_s = cursor_screen.x + cursor_screen.y;

	while (cursor_s < limit_h)
	{
		//printf("cursor_s %d %d\n", cursor_s, limit_h);
		cursor_s = cursor_screen.x + cursor_screen.y;
		while (cursor_screen.x < width.y)
		{
			cursor_t = cursor_txtr.x + cursor_txtr.y;
			arch->sdl->screen[cursor_s] = enemy->sprites->pixels[cursor_t];
			cursor_screen.x++;
			cursor_s++;
			buff_cursor.x += buff_w;
			cursor_txtr.x = (int)buff_cursor.x;
		}
		cursor_screen.x = width.x;
		buff_cursor.x = start_x_txtr;
		cursor_screen.y += arch->sdl->size.x;
		buff_cursor.y += buff_h;
		cursor_txtr.y = (int)buff_cursor.y * enemy->sprites->w;
	}
}
*/

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

	p_buff_h = (double)enemy->sprites->h / (double)(heigth.y - heigth.x);
	p_buff_w = enemy->sprites->w / (double)(width.y - width.x);

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
					enemy->sprites->pixels[(int)buffer_w + (int)buffer_h * enemy->sprites->w];
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
		enemy_node->sprites = &sector->txtrsol;
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
			//printf("dist cam .x %f .y %f\n", dist_cam.x, dist_cam.y);
			posx = arch->sdl->size.x / 2 - dist_cam.y / dist_cam.x * arch->cam->d_screen;
			//printf("posx %d\n", posx);
			arch->sdl->screen[posx + (arch->sdl->size.y / 2) * arch->sdl->size.x] = 0xffffffff;
			//printf("enemy heigth %f\n", enemy_node->stat.height);
			enemy_surface = cam_get_enemy_surface(arch->cam, arch->sdl, enemy_node, player, dist_cam.x);
			//printf("enemy surface %d %d\n", enemy_surface.x, enemy_surface.y);
			sdl_line(arch->sdl, (t_vct2){posx, enemy_surface.x}, (t_vct2){posx, enemy_surface.y}, BLUE_SOFT);
			//proportion avec les texture
			//printf("enemy surface len w %d h %d\n", enemy_node->sprites->w, enemy_node->sprites->h);
			enemy_width = cam_enemy_width(arch->cam, enemy_node, enemy_surface, posx);
			arch->sdl->screen[enemy_width.x + (arch->sdl->size.y / 2) * arch->sdl->size.x] = 0x00ffffff;
			sdl_line(arch->sdl, (t_vct2){enemy_width.x, arch->sdl->size.y / 2}, (t_vct2){enemy_width.y, arch->sdl->size.y / 2}, YELLOW);
			draw_enemy_box(arch, enemy_node, enemy_width, enemy_surface, neutral_distance);
		}
		enemy_node = enemy_node->next;
	}
}