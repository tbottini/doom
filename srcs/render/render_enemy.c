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

void			draw_enemy_box(t_sdl *sdl, t_enemy *enemy, t_vct2 width, t_vct2 heigth)
{
	double		buff_h;
	double		buff_w;
	t_vct2		cursor_screen;
	t_vct2		cursor_txtr;
	t_fvct2		buff_cursor;
	double		start_x_txtr;

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
		cursor_screen.y = heigth.x;
	}
	if (heigth.y > sdl->size.y)
		heigth.y = sdl->size.y;
	if (width.y > sdl->size.x)
		width.y = sdl->size.x;
	while (cursor_screen.y < heigth.y)
	{
		while (cursor_screen.x < width.y)
		{
			sdl->screen[cursor_screen.x + cursor_screen.y * sdl->size.x] = enemy->sprites->pixels[cursor_txtr.x + cursor_txtr.y * enemy->sprites->w];
			cursor_screen.x++;
			buff_cursor.x += buff_w;
			cursor_txtr.x = (int)buff_cursor.x;
		}
		cursor_screen.x = width.x;
		buff_cursor.x = start_x_txtr;
		cursor_screen.y++;
		buff_cursor.y += buff_h;
		cursor_txtr.y = (int)buff_cursor.y;
	}
}

void			render_sector_enemy(t_sdl *sdl, t_camera *camera, t_sector *sector, t_player *player)
{
	t_enemy		*enemy_node;
	double		e_angle;
	t_fvct2		dist_cam;
	int			posx;
	t_vct2		enemy_surface;
	t_vct2		enemy_width;

	enemy_node = sector->enemys;


	if (!enemy_node && debug == 8)
		printf("no enemy\n");
	while (enemy_node)
	{
		enemy_node->sprites = &sector->txtrsol;
		printf("pos %f %f\n", enemy_node->stat.pos.x, enemy_node->stat.pos.y);
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&enemy_node->stat.pos, player->stat.rot.y);
		printf("e_angle %f\n", e_angle);
		if (e_angle < 90 && e_angle > -90)
		{
			dist_cam.x = distance(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&enemy_node->stat.pos);
			dist_cam.y = dist_cam.x * sin(e_angle * TO_RADIAN);
			dist_cam.x = dist_cam.x * cos(e_angle * TO_RADIAN);
			b_point_debug(dist_cam, RED);
			printf("dist cam .x %f .y %f\n", dist_cam.x, dist_cam.y);
			posx = sdl->size.x / 2 - dist_cam.y / dist_cam.x * camera->d_screen;
			printf("posx %d\n", posx);
			sdl->screen[posx + (sdl->size.y / 2) * sdl->size.x] = 0xffffffff;
			printf("enemy heigth %f\n", enemy_node->stat.height);
			enemy_surface = cam_get_enemy_surface(camera, sdl, enemy_node, player, dist_cam.x);
			printf("enemy surface %d %d\n", enemy_surface.x, enemy_surface.y);
			sdl_line(sdl, (t_vct2){posx, enemy_surface.x}, (t_vct2){posx, enemy_surface.y}, BLUE_SOFT);
			//proportion avec les texture
			printf("enemy surface len w %d h %d\n", enemy_node->sprites->w, enemy_node->sprites->h);
			enemy_width = cam_enemy_width(camera, enemy_node, enemy_surface, posx);
			sdl->screen[enemy_width.x + (sdl->size.y / 2) * sdl->size.x] = 0x00ffffff;
			sdl_line(sdl, (t_vct2){enemy_width.x, sdl->size.y / 2}, (t_vct2){enemy_width.y, sdl->size.y / 2}, YELLOW);
			draw_enemy_box(sdl, enemy_node, enemy_width, enemy_surface);
		}
		enemy_node = enemy_node->next;
	}
}