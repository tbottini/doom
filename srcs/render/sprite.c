#include "render.h"
#include "calcul.h"
#include "debug.h"

void				sprite_insert(t_sprite **sprite_list, t_sprite *sprite_node)
{
	t_sprite		*sprite_insert;

	sprite_insert = *sprite_list;
	if (!sprite_insert)
	{
		if (debug == 9)
			printf("insert first node %f\n", sprite_node->pos.x);
		*sprite_list = sprite_node;
	}
	else if (sprite_node->pos.x > sprite_insert->pos.x)
	{
		if (debug == 9)
			printf("insert2node %f\n", sprite_node->pos.x);
		sprite_node->next = *sprite_list;
		*sprite_list = sprite_node;
	}
	else
	{
		while (sprite_insert->next && sprite_node->pos.x < sprite_insert->next->pos.x)
		{
			printf("next\n");
			sprite_insert= sprite_insert->next;
		}
		sprite_node->next = sprite_insert->next;
		sprite_insert->next = sprite_node;
		if (debug == 9)
			printf("insert node %f\n", sprite_node->pos.x);
	}
}

t_sprite			*sprite_new(t_txtr texture, t_fvct3 origin, t_fvct3 dist, double angle)
{
	t_sprite		*sprite;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->texture = texture;
	sprite->next = NULL;
	sprite->pos.x = distance(*(t_fvct2*)&origin, *(t_fvct2*)&dist);
	sprite->pos.y = sprite->pos.x * sin(angle * TO_RADIAN);
	sprite->pos.x = sprite->pos.x * cos(angle * TO_RADIAN);
	return (sprite);
}

void				sprite_free(t_sprite *sprite)
{
	if (sprite)
	{
		free(sprite);
		sprite = NULL;
	}
}

void				sprite_print(t_sprite *sprite)
{
	printf("sprite pos .x %f .y %f\n", sprite->pos.x, sprite->pos.y);
}

void				sprite_iter(t_sprite *sprite, void(*effector)(t_sprite*))
{
	while (sprite)
	{
		effector(sprite);
		sprite = sprite->next;
	}
}

t_sprite			*sprite_from_enemy(t_sprite **sprite_list, t_enemy *enemy, t_player *player, t_arch *arch)
{
	t_sprite		*sprite;
	double			e_angle;
	int				posx;

	while (enemy)
	{
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&enemy->stat.pos, player->stat.rot.y);
		if (e_angle < 90 && e_angle > -90)
		{
			enemy->sprites = &enemy->stat.sector->txtrsol;
			sprite = sprite_new(enemy->stat.sector->txtrsol, player->stat.pos, enemy->stat.pos, e_angle);
			if (!sprite)
				sprite_iter(*sprite_list, &sprite_free);
			posx = arch->sdl->size.x / 2 - sprite->pos.y / sprite->pos.x * arch->cam->d_screen;
			sprite->heigth = cam_get_enemy_surface(arch->cam, arch->sdl, enemy, player, sprite->pos.x);
			sprite->width = cam_txtr_width(arch->cam, &sprite->texture, sprite->heigth, posx);
			sprite_insert(sprite_list, sprite);
		}
		enemy = enemy->next;
	}
	return (*sprite_list);
}


t_sprite			*sprite_from_props(t_sprite **sprite_list, t_prop *props, t_player *player, int len, t_arch *arch)
{
	t_sprite		*sprite;
	double			e_angle;
	int				i;
	int				posx;


	i = 0;
	while (i < len)
	{
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos, *(t_fvct2*)&props[i].pos, player->stat.rot.y);
		if (e_angle < 90 && e_angle > -90)
		{
			sprite = sprite_new(props[i].sector->txtrtop, player->stat.pos, props[i].pos, e_angle);
			if (!sprite)
				sprite_iter(*sprite_list, &sprite_free);
			posx = arch->sdl->size.x / 2 - sprite->pos.y / sprite->pos.x * arch->cam->d_screen;

			//sprite->heigth =
			sprite->heigth = player_prop_heigth_surface(arch, player, &props[i], sprite->pos.x);
			sprite->width = cam_txtr_width(arch->cam, &sprite->texture, sprite->heigth, posx);
			sprite_insert(sprite_list, sprite);
		}
		i++;
	}
	return (*sprite_list);
}

void				sprite_render(t_sprite *sprite, t_arch *arch, t_player *player)
{
	double		p_buff_h;
	double		p_buff_w;
	double		start_txtr_heigth;
	double		buffer_h;
	double		buffer_w;
	int			i_heigth;
	int			limit_h;
	int			cursor_screen;
	double		neutral_distance;

	p_buff_h = (double)sprite->texture.h / (double)(sprite->heigth.y - sprite->heigth.x);
	p_buff_w = sprite->texture.w / (double)(sprite->width.y - sprite->width.x);
	neutral_distance = (double)(arch->sdl->size.y) / sprite->pos.x;
	if (sprite->heigth.x < 0)
	{
		sprite->heigth.x = 0;
		start_txtr_heigth = -sprite->heigth.x * p_buff_h;
	}
	else
	{
		start_txtr_heigth = 0;
	}
	if (sprite->width.x < 0)
	{
		buffer_w = -sprite->width.x * p_buff_w;
		sprite->width.x = 0;
	}
	else
	{
		buffer_w = 0;
	}
	if (sprite->width.y > arch->sdl->size.x)
		sprite->width.y = arch->sdl->size.x;
	if (sprite->heigth.y > arch->sdl->size.y)
		sprite->heigth.y = arch->sdl->size.y - 1;
	while (sprite->width.x < sprite->width.y)
	{
		if (zline_compare(arch, neutral_distance, sprite->width.x))
		{
			if (sprite->heigth.x < (int)arch->portal.b_up[sprite->width.x])
			{
				i_heigth = (int)arch->portal.b_up[sprite->width.x];
				buffer_h = (arch->portal.b_up[sprite->width.x] - sprite->heigth.x) * p_buff_h;
			}
			else
			{
				i_heigth = sprite->heigth.x;
				buffer_h = 0;
			}
			cursor_screen = sprite->width.x + (i_heigth * arch->sdl->size.x);
			if (sprite->heigth.y > (int)arch->portal.b_down[sprite->width.x])
				limit_h = arch->portal.b_down[sprite->width.x] * arch->sdl->size.x;
			else
				limit_h = sprite->heigth.y * arch->sdl->size.x;


			while (cursor_screen < limit_h)
			{
				arch->sdl->screen[cursor_screen] =
					sprite->texture.pixels[(int)buffer_w + (int)buffer_h * sprite->texture.w];
				cursor_screen += arch->sdl->size.x;
				buffer_h += p_buff_h;
			}
		}
		sprite->width.x++;
		buffer_w += p_buff_w;
	}
}

void			sprite_render_list(t_sprite *sprite, t_arch *arch, t_player *player)
{
	while (sprite)
	{
		sprite_render(sprite, arch, player);
		sprite = sprite->next;
	}
}