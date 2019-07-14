/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 17:09:52 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEPX 100.0
#define EDITORSTEPY -100.0

void	set_txtr(t_editor *edit, SDL_Texture **txtr, int id)
{
	if (edit->idtoeditor[id] == -1)
		*txtr = NULL;
	else
		*txtr = edit->txtrgame[edit->idtoeditor[id]];
}

int	read_balise(int fd, char *balise, int ret)
{
	int *x;
	int y;

	x = (int *)balise;
	read(fd, &y, sizeof(y));
	if (*x != y)
		return (ret);
	return (0);
}

int find_id_from_path(char **txtrname, char *path)
{
	int x;

	x = 0;
	while (txtrname[x] && x < MAXTXTRNUMBER)
	{
		if (ft_strcmp(txtrname[x], path) == 0)
			return (x);
		x++;
	}
	return (-1);
}

int	read_one_texture(int fd, t_editor *edit, int x)
{
	int pathlen;
	char path[512];
	SDL_Surface *tmp;

	if (read(fd, &pathlen, sizeof(int)) != sizeof(int) || pathlen >= 512 || pathlen <= 0)
		return (-23);
	printf("\tString Len: %d\n", pathlen);
	if (read(fd, path, sizeof(char) * (pathlen + 1)) != sizeof(char) * (pathlen + 1))
		return (-24);
	path[pathlen] = '\0';
	printf("\tString : %s\n", path);
	edit->idtoeditor[x] = find_id_from_path(edit->txtrname, path);
	if (read(fd, path, sizeof(char)) != sizeof(char) || *path != '\v')
		return (-26);
	printf("\tGOOD\n\n");
	return (0);
}

int read_textures(int fd, t_editor *edit, t_slen *len)
{
	int x;
	int rtn;

	if (read_balise(fd, "🌅", -2))
		return (-2);
	if (read(fd, &len->nb_txtrs, sizeof(int)) != sizeof(int))
		return (-21);
	printf("Found %d Textures\n", len->nb_txtrs);
	if (!(edit->idtoeditor = malloc(sizeof(int) * len->nb_txtrs)))
		return (-22);
	x = 0;
	while (x < len->nb_txtrs)
	{
		if ((rtn = read_one_texture(fd, edit, x)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🌌", 2))
		return (2);
	return (0);
}

int	read_one_pillar(int fd, t_lstpil *pillars)
{
	t_fvct2 p;
	t_vct2 edp;

	if ((read(fd, &p.x, sizeof(double))) != sizeof(double))
		return (-32);
	if (read(fd, &p.y, sizeof(double)) != sizeof(double))
		return (-33);
	edp.x = p.x * EDITORSTEPX;
	edp.y = p.y * EDITORSTEPY;
	ft_pillarpushend(pillars, edp);
	printf("\tNew Pillar at %f\t%f\n", p.x, p.y);
	return (0);
}

int	read_pillars(int fd, t_lstpil *pillars, t_slen *len)
{
	int x;
	int rtn;

	if (read_balise(fd, "⛩", -3))
		return (-3);
	if ((read(fd, &len->nb_pills, sizeof(int)) != sizeof(int)) || len->nb_pills < 0)
		return (-31);
	printf("Found %d Pillars\n", len->nb_pills);
	x = 0;
	while (x < len->nb_pills)
	{
		if ((rtn = read_one_pillar(fd, pillars)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "💊", 3))
		return (3);
	return (0);
}

int	read_one_prop(int fd, t_game *game, t_prop *prop, t_slen *len)
{
	int		var_a;
	int		var_b;

	if (read(fd, &prop->type, sizeof(int)) != sizeof(int))
		return (-72);
	printf("\t\tFound Prop type: %d\n", prop->type);
	if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a >= len->nb_sects)
		return (-73);
	printf("\t\tFound Prop Sector ID: %d\n", var_a);
	prop->sector = &game->sectors[var_a];
	if ((read(fd, &var_b, sizeof(int)) != sizeof(int)) || var_b >= len->nb_sects)
		return (-74);
	if (var_b == -1)
	{
		if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a != -1)
			return (-79);
	}
	else if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a >= game->sectors[var_b].len)
		return (-75);
	printf("\t\tFound wall %d in sector %d\n", var_a, var_b);
	prop->wall = &game->sectors[var_b].wall[var_a];
	if ((read(fd, &prop->pos.x, sizeof(double)) != sizeof(double)))
		return (-76);
	if ((read(fd, &prop->pos.y, sizeof(double)) != sizeof(double)))
		return (-77);
	init_prop(prop);
	printf("\t\tSet Wall Prop position %f %f\n", prop->pos.x, prop->pos.y);
	return (0);
}

int	read_wall_props(int fd, t_editor *edit, t_mur *wall, t_slen *len)
{
	int x;
	int	nbp;
	int rtn;
	t_entity *ent;

	if (read_balise(fd, "🖼", -7))
		return (-7);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)) || nbp < 0)
		return (-71);
	printf("\t\tFound %d Wall Props\n", nbp);
	x = 0;
	while (x < nbp)
	{
		if (!(ent = ft_enemypushend(&wall->wproplist, (t_vct2){0, 0}, MINPROPSPOS, NULL)))
			return (NULL);
		if ((rtn = read_one_prop(fd, edit, &(wall->props[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "📅", 7))
		return (7);
	return (0);
}

t_pilier *find_pilier_by_id(t_lstpil pils, int id)
{
	if (id < 0)
		return (NULL);
	while (id >= 0 && pils)
	{
		if (id == 0)
			return (pils);
		pils = pils->next;
		id--;
	}
	return (NULL);
}

int	read_one_wall(int fd, t_editor *edit, t_mur *wall, t_slen *len)
{
	int	tmp;

	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-61);
	printf("\t\tFound Pillar1 ID: %d\n", tmp);
	wall->pil1 = find_pilier_by_id(edit->pillist, tmp);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-62);
	printf("\t\tFound Pillar2 ID: %d\n", tmp);
	wall->pil2 = find_pilier_by_id(edit->pillist, tmp);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_txtrs))
		return (-63);
	printf("\t\tFound Texture ID: %d\n", tmp);
	set_txtr(edit, &wall->txtr, tmp);
	if (((read(fd, &wall->portal_id, sizeof(t_portal_id)) != sizeof(t_portal_id))))
		return (-64);
	printf("\t\tFound Wall Type: %d\n", tmp);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects))
		return (-65);
	printf("\t\tFound Wall Sector Link: %d\n", tmp);
	wall->portal_ptr = NULL;
	return (read_wall_props(fd, edit, wall, len));
}

int	read_sec_walls(int fd, t_editor *edit, t_lstmur *mur, t_slen *len)
{
	int x;
	int	nbw;
	int rtn;
	t_mur *wall;

	if (read_balise(fd, "💦", -6))
		return (-6);
	if ((read(fd, &nbw, sizeof(int)) != sizeof(int)))
		return (-61);
	printf("\t\tFound %d Walls\n", nbw);
	x = 0;
	while (x < nbw)
	{
		if (!(wall = ft_wallpushend(mur, NULL, NULL, NULL)))
			return (-62);
		if ((rtn = read_one_wall(fd, edit, wall, len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "⛱", -6))
		return (-5);
	return (0);
}

int	read_sec_props(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	int x;
	int	nbp;
	int rtn;

	if (read_balise(fd, "🚽", -8))
		return (-8);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)))
		return (-81);
	printf("\tFound %d Props\n", nbp);
	if (!(sector->props = (t_prop *)malloc(sizeof(t_prop) * (nbp + 1))))
		return (-428);
	ft_bzero(sector->props, sizeof(t_prop) * (nbp + 1));
	x = 0;
	while (x < nbp)
	{
		if ((rtn = read_one_prop(fd, game, &(sector->props[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "💩", 8))
		return (8);
	return (0);
}

int	read_one_sector(int fd, t_editor *edit, t_secteur *sec, t_slen *len)
{
	char	ctmp;
	int		itmp;
	double	dtmp;

	if (read(fd, &ctmp, sizeof(char)) != sizeof(char))
		return (-51);
	sec->gravity = (ctmp ? G_EARTH : G_MOON);
	if (read(fd, &dtmp, sizeof(double)) != sizeof(double))
		return (-52);
	sec->hsol = dtmp * EDITORSTEPX;
	if (read(fd, &dtmp, sizeof(double)) != sizeof(double))
		return (-53);
	sec->htop = dtmp * EDITORSTEPX;
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-54);
	set_txtr(edit, &sec->sol, itmp);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-55);
	set_txtr(edit, &sec->top, itmp);
	if ((itmp = read_sec_walls(fd, edit, &sec->murs, len)))
		return (itmp);
	return (read_sec_props(fd, edit, sec, len));
}

int	read_sectors(int fd, t_editor *edit, t_slen *len)
{
	int x;
	int rtn;
	t_secteur *sec;

	if (read_balise(fd, "🚧", -5))
		return (-5);
	if ((read(fd, &len->nb_sects, sizeof(int)) != sizeof(int)) || len->nb_sects < 0)
		return (-51);
	printf("Found %d sectors\n", len->nb_sects);
	x = 0;
	while (x < len->nb_sects)
	{
		if (!(sec = push_secteur(&edit->sectors, NULL, NULL)))
			return (-52);
		if ((rtn = read_one_sector(fd, edit, sec, len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🏠", 5))
		return (5);
	return (0);
}

int	read_player(int fd, t_game *game, t_player *player, t_slen *len)
{
	int tmp;

	if (read_balise(fd, "🍆", -9))
		return (-9);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects)
		return (-91);
	printf("Found Player at %d\n", tmp);
	player->stat.sector = &game->sectors[tmp];
	if ((read(fd, &player->stat.health, sizeof(int)) != sizeof(int)))
		return (-92);
	printf("Player Health: %d\n", player->stat.health);
	if ((read(fd, &player->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-93);
	if ((read(fd, &player->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-94);
	printf("Player Pos: %f %f\n", player->stat.pos.x, player->stat.pos.y);
	if ((read(fd, &player->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-95);
	printf("Player Rot: %f\n", player->stat.rot.y);
	if (read_balise(fd, "🍌", 9))
		return (9);
	return (0);
}

int	read_one_enemy(int fd, t_game *game, t_slen *len)
{
	t_enemy *enemy;
	int tmp;

	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || !(ISENEMY(tmp)))
		return (-101);
	enemy = enemy_init(tmp);
	printf("\tEnemy type: %d\n", tmp);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)))
		return (-102);
	printf("\tEnemy Sector: %d\n", tmp);
	if ((read(fd, &enemy->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-103);
	if ((read(fd, &enemy->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-104);
	printf("Enemy Pos: %f %f\n", enemy->stat.pos.x, enemy->stat.pos.y);
	if ((read(fd, &enemy->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-105);
	printf("Enemy Rot: %f\n", enemy->stat.rot.y);
	if (0 <= tmp && tmp < len->nb_sects)
		pushfront_enemy(&game->sectors[tmp], enemy);
	else
		free(enemy);
	return (0);
}

int	read_enemies(int fd, t_game *game, t_slen *len)
{
	int	x;
	int	rtn;
	int	nbe;

	if (read_balise(fd, "🔪", -10))
		return (-10);
	if ((read(fd, &nbe, sizeof(int)) != sizeof(int)))
		return (-11);
	printf("Found %d enemies\n", nbe);
	x = 0;
	while (x < nbe)
	{
		if ((rtn = read_one_enemy(fd, game, len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🍹", 10))
		return (10);
	return (0);
}

static int reading_map(int fd, t_editor *edit, t_slen *len)
{
	long	x;
	long	*tmp;
	int		rtn;

	read(fd, &x, sizeof(x));
	tmp = (long *)"💎🇩🇿🍉💩";
	if (x != *tmp)
		return (1);
	if ((rtn = read_textures(fd, edit, len)))
		return (rtn);
	if ((rtn = read_pillars(fd, &edit->pillist, len)))
		return (rtn);
	if ((rtn = read_sectors(fd, edit, len)))
		return (rtn);
	if ((rtn = read_player(fd, &doom->game, &doom->game.player, len)))
		return (rtn);
	if ((rtn = read_enemies(fd, &doom->game, len)))
		return (rtn);
	read(fd, &x, sizeof(x));
	tmp = (long *)"👨🏻🤠🍑";
	if (x != *tmp)
		return (-1);
	return (0);
}

int	read_file_to_editor(t_editor *edit, const char *file)
{
	int		fd;
	int		returncode;
	t_slen	len;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	if ((returncode = reading_map(fd, edit, &len)))
	{
		if (edit->idtoeditor)
		{
			free(edit->idtoeditor);
			edit->idtoeditor = NULL;
		}
		ft_printf("Error : %d\n", returncode);
		close(fd);
		return (-1);
	}
	if (edit->idtoeditor)
	{
		free(edit->idtoeditor);
		edit->idtoeditor = NULL;
	}
	close(fd);
	write(1, "Successfully read ressources/map/editor.map\n", 44);
	return (0);
}
