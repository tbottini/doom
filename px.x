srcs/debug/debug_screen.c:7:	vct.x = arch->sdl->size.x / 2.0 + vct.x * arch->zoom;
srcs/debug/debug_screen.c:8:	vct.y = arch->sdl->size.y / 2.0 - vct.y * arch->zoom;
srcs/debug/debug_screen.c:66:	screen = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
srcs/debug/debug_screen.c:84:	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
srcs/debug/debug_screen.c:86:	borne_up.a = tan(PI180 * arch->portal.b_left);
srcs/debug/debug_screen.c:87:	borne_down.a = tan(PI180 * arch->portal.b_right);
srcs/debug/debug_screen.c:90:	point1.x = arch->sdl->size.x / 2.0;
srcs/debug/debug_screen.c:91:	point1.y = arch->sdl->size.y / 2.0;
srcs/debug/debug_screen.c:92:	point2.x = arch->sdl->size.x - 1;
srcs/debug/debug_screen.c:93:	point2.y = arch->sdl->size.y / 2 - affine_val(borne_up, point2.x / 2.0);
srcs/debug/debug_screen.c:94:	fill_line_debug(arch, arch->sdl, point1, point2, color);
srcs/debug/debug_screen.c:95:	point2.y = arch->sdl->size.y / 2 - affine_val(borne_down, point2.x / 2.0);
srcs/debug/debug_screen.c:96:	fill_line_debug(arch, arch->sdl, point1, point2, color);
srcs/debug/debug_screen.c:104:	point1.x = arch->sdl->size.x / 2.0 + (arch->pillar.x * arch->zoom);
srcs/debug/debug_screen.c:105:	point1.y = arch->sdl->size.y / 2.0 - (arch->pillar.y * arch->zoom);
srcs/debug/debug_screen.c:106:	point2.x = arch->sdl->size.x / 2.0 + (arch->next.x * arch->zoom);
srcs/debug/debug_screen.c:107:	point2.y = arch->sdl->size.y / 2.0 - (arch->next.y * arch->zoom);
srcs/debug/debug_screen.c:108:	fill_line_debug(arch, arch->sdl, point1, point2, color);
srcs/debug/debug_screen.c:117:	mid.x = arch->sdl->size.x / 2.0;
srcs/debug/debug_screen.c:118:	mid.y = arch->sdl->size.y / 2.0;
srcs/debug/debug_screen.c:119:	v.x = arch->sdl->size.x / 2.0 + a.x * arch->zoom;
srcs/debug/debug_screen.c:120:	v.y = arch->sdl->size.y / 2.0 - a.y * arch->zoom;
srcs/debug/debug_screen.c:121:	fill_line_debug(arch, arch->sdl, mid, v, color);
srcs/debug/debug_screen.c:134:	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
srcs/debug/debug_screen.c:138:	portion.x = (portion.x - arch->sdl->size.x / 2.0) / arch->zoom;
srcs/debug/debug_screen.c:139:	portion.y = (portion.y - arch->sdl->size.x / 2.0) / arch->zoom;
srcs/debug/debug_screen.c:140:	point1.y = arch->sdl->size.y / 2.0 - affine_val(affine, portion.x) * arch->zoom;
srcs/debug/debug_screen.c:141:	point2.y = arch->sdl->size.y / 2.0 - affine_val(affine, portion.y) * arch->zoom;
srcs/debug/debug_screen.c:150:		portion = (t_fvct2){0, arch->sdl->size.x - 1};
srcs/debug/debug_screen.c:152:		portion = (t_fvct2){arch->sdl->size.x / 2, arch->sdl->size.x - 1};
srcs/debug/debug_screen.c:165:	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
srcs/debug/debug_screen.c:166:	pt1.x = arch->sdl->size.x / 2 + px_distance;
srcs/debug/debug_screen.c:168:	pt1.y = arch->sdl->size.y / 2 + (px_distance * fov_affine.a);
srcs/debug/debug_screen.c:169:	pt2.y = arch->sdl->size.y / 2 + (px_distance * -fov_affine.a);
srcs/debug/debug_screen.c:183:		fov_affine.a = tan((arch->cam->fov / 2.0) * PI180);
srcs/debug/debug_screen.c:188:		fov_affine.a = tan(arch->cam->fov_ver / 2 );
srcs/debug/debug_screen.c:199:		draw_screen(arch, color, arch->sdl->size.x / 12, fov_affine);
srcs/debug/debug_screen.c:214:	dist = arch->sdl->size.x / 2.5;
srcs/debug/debug_screen.c:215:	fov_affine.a = tan(arch->cam->fov_ver / 2);
srcs/debug/debug_screen.c:220:	point1.x = dist + arch->sdl->size.x / 2;
srcs/debug/debug_screen.c:221:	point2.x = dist + arch->sdl->size.x / 2;
srcs/debug/debug_screen.c:223:	point1.y = len_screen * (surface_pillar.x / arch->sdl->size.y) + (arch->sdl->size.y - len_screen) / 2;
srcs/debug/debug_screen.c:224:	point2.y =  len_screen * (surface_pillar.y / arch->sdl->size.y) + (arch->sdl->size.y - len_screen) / 2;
srcs/debug/debug_screen.c:225:	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
srcs/debug/debug_screen.c:235:		a_pillar = (t_affine){arch->pillar.y / arch->pillar.x, 0, 0};
srcs/debug/debug_screen.c:239:			b_point_debug(arch->pillar, RED);
srcs/debug/debug_screen.c:243:		a_pillar = (t_affine){arch->next.y / arch->next.x, 0, 0};
srcs/debug/debug_screen.c:247:			b_point_debug(arch->next, RED);
srcs/debug/debug_screen.c:256:	while (i < arch->sdl->size.x * arch->sdl->size.y)
srcs/debug/debug_screen.c:258:		if (arch->sc_debug[i] != 0)
srcs/debug/debug_screen.c:259:			arch->sdl->screen[i] = arch->sc_debug[i];
srcs/manager/arch_manager.c:11:	while (i < arch->sdl->size.x)
srcs/manager/arch_manager.c:13:		arch->portal.b_up[i] = 0;
srcs/manager/arch_manager.c:14:		arch->portal.b_down[i] = arch->sdl->size.y;
srcs/manager/arch_manager.c:17:	arch->portal.b_left = arch->cam->fov / 2.0;
srcs/manager/arch_manager.c:18:	arch->portal.b_right = -arch->cam->fov / 2.0;
srcs/manager/arch_manager.c:26:	while (i < arch->sdl->size.x)
srcs/manager/arch_manager.c:28:		arch->portal.zline[i] = 0;
srcs/manager/arch_manager.c:41:	free(arch->portal.zline);
srcs/manager/arch_manager.c:49:	arch->portal.zline = (double*)malloc(sizeof(double) * sdl->size.x);
srcs/manager/arch_manager.c:50:	if (!arch->portal.zline)
srcs/manager/arch_manager.c:53:	arch->sdl = sdl;
srcs/manager/arch_manager.c:54:	arch->cam = cam;
srcs/manager/arch_manager.c:55:	arch->portal.b_down = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
srcs/manager/arch_manager.c:56:	if (!arch->portal.b_down)
srcs/manager/arch_manager.c:58:	arch->portal.b_up = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
srcs/manager/arch_manager.c:59:	if (!arch->portal.b_up)
srcs/manager/arch_manager.c:61:	arch->wall = NULL;
srcs/manager/arch_manager.c:62:	arch->depth_portal = 0;
srcs/manager/arch_manager.c:63:	arch->zoom = 25;
srcs/render/drawer/draw_column.c:25:	if (surface.y < (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:26:		return (numcol + surface.y * arch->sdl->size.x);
srcs/render/drawer/draw_column.c:27:	if (surface.x < (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:29:		buff = (-surface.x + arch->portal.b_up[arch->px.x]) * coef;
srcs/render/drawer/draw_column.c:35:		surface.x = arch->portal.b_up[arch->px.x];
srcs/render/drawer/draw_column.c:37:	while (surface.x < surface.y && surface.x < (int)arch->portal.b_down[arch->px.x])
srcs/render/drawer/draw_column.c:39:		arch->sdl->screen[numcol] = txtr->pixels[px];
srcs/render/drawer/draw_column.c:41:		numcol += arch->sdl->size.x;
srcs/render/drawer/draw_column.c:64:	if (surface.y < (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:65:		return (numcol + surface.y * arch->sdl->size.x);
srcs/render/drawer/draw_column.c:66:	if (surface.x < (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:68:		buff = (-surface.x + arch->portal.b_up[arch->px.x]) * coef;
srcs/render/drawer/draw_column.c:74:		surface.x = arch->portal.b_up[arch->px.x];
srcs/render/drawer/draw_column.c:76:	while (surface.x < surface.y && surface.x < (int)arch->portal.b_down[arch->px.x])
srcs/render/drawer/draw_column.c:78:		arch->sdl->screen[numcol] = txtr->pixels[px];
srcs/render/drawer/draw_column.c:80:		numcol += arch->sdl->size.x;
srcs/render/drawer/draw_column.c:99:	if (surface.x >= (int)arch->portal.b_down[arch->px.x])
srcs/render/drawer/draw_column.c:101:		return (arch->portal.b_down[arch->px.x] * arch->sdl->size.x + arch->px.x);
srcs/render/drawer/draw_column.c:103:	else if (surface.y <= (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:105:		return (arch->portal.b_up[arch->px.x] * arch->sdl->size.x + arch->px.x);
srcs/render/drawer/draw_column.c:107:	if (surface.x <= (int)arch->portal.b_up[arch->px.x])
srcs/render/drawer/draw_column.c:108:		surface.x = arch->px.x + arch->portal.b_up[arch->px.x] * arch->sdl->size.x;
srcs/render/drawer/draw_column.c:110:		surface.x = surface.x * arch->sdl->size.x + arch->px.x;
srcs/render/drawer/draw_column.c:111:	if (surface.y > (int)arch->portal.b_down[arch->px.x])
srcs/render/drawer/draw_column.c:112:		surface.y = arch->px.x + (arch->portal.b_down[arch->px.x] - 1) * arch->sdl->size.x;
srcs/render/drawer/draw_column.c:114:		surface.y = surface.y * arch->sdl->size.x;
srcs/render/drawer/draw_column.c:117:		arch->sdl->screen[surface.x] = color;
srcs/render/drawer/draw_column.c:118:		surface.x += arch->sdl->size.x;
srcs/render/drawer/draw_column.c:128:	surface_tmp = (t_vct2){arch->portal.b_up[arch->px.x], surface.x};
srcs/render/drawer/draw_column.c:131:	draw_part_texture(arch, cursor, surface_tmp, &arch->wall->txtr);
srcs/render/drawer/draw_column.c:132:	surface_tmp = (t_vct2){surface.y, arch->portal.b_down[arch->px.x]};
srcs/render/drawer/draw_column.c:141:**	-->renvoie sans le facteur largeur (arch->sdl->size.x)
srcs/render/drawer/draw_column.c:171:	s_portal = surface_portal(surface, arch->sector, arch->wall->link);
srcs/render/drawer/draw_column.c:173:	tmp = (t_vct2){arch->portal.b_up[arch->px.x], surface.x};
srcs/render/drawer/draw_column.c:176:	surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
srcs/render/drawer/draw_column.c:180:	surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
srcs/render/drawer/draw_column.c:181:	tmp = (t_vct2){surface.y, arch->portal.b_down[arch->px.x]};
srcs/render/drawer/draw_column.c:183:	parent_borne->b_up[arch->px.x - start] = arch->portal.b_up[arch->px.x];
srcs/render/drawer/draw_column.c:184:	parent_borne->b_down[arch->px.x - start] = arch->portal.b_down[arch->px.x];
srcs/render/drawer/draw_column.c:187:	set_borne_vertical(arch, tmp, arch->px.x);
srcs/render/drawer/draw_line.c:77:	screen = arch->sc_debug;
srcs/render/drawer/render_wall.c:16:	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
srcs/render/drawer/render_wall.c:63:	if (arch->px.x > arch->px.y)
srcs/render/drawer/render_wall.c:65:		tmpint = arch->px.x;
srcs/render/drawer/render_wall.c:66:		arch->px.x = arch->px.y;
srcs/render/drawer/render_wall.c:67:		arch->px.y = tmpint;
srcs/render/drawer/render_wall.c:68:		pillar_tmp = arch->pillar;
srcs/render/drawer/render_wall.c:69:		arch->pillar = arch->next;
srcs/render/drawer/render_wall.c:70:		arch->next = pillar_tmp;
srcs/render/drawer/render_wall.c:71:		tmp = arch->shift_txtr.x;
srcs/render/drawer/render_wall.c:72:		arch->shift_txtr.x = arch->shift_txtr.y;
srcs/render/drawer/render_wall.c:73:		arch->shift_txtr.y = tmp;
srcs/render/drawer/render_wall.c:81:**		-la borne pour la recursivite arch->portal
srcs/render/drawer/render_wall.c:82:**		-recharge borne_tmp dans arch->portal
srcs/render/drawer/render_wall.c:94:	start = arch->px.x;
srcs/render/drawer/render_wall.c:95:	coef_surface.x = coef_diff(pillar->x - next->x, arch->px);
srcs/render/drawer/render_wall.c:96:	coef_surface.y = coef_diff(pillar->y - next->y, arch->px);
srcs/render/drawer/render_wall.c:97:	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
srcs/render/drawer/render_wall.c:98:	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
srcs/render/drawer/render_wall.c:99:	coef_neutre = coef_vct(neutre, arch->px);
srcs/render/drawer/render_wall.c:102:	coef_distance = (arch->next.x - arch->pillar.x) / (arch->px.y - arch->px.x);
srcs/render/drawer/render_wall.c:103:	dist_px = arch->pillar.x;
srcs/render/drawer/render_wall.c:104:	while (arch->px.x != arch->px.y)
srcs/render/drawer/render_wall.c:106:		if (arch->wall->status == WALL)
srcs/render/drawer/render_wall.c:108:			if (z_line_buffer(arch, neutre.x, arch->px.x))
srcs/render/drawer/render_wall.c:111:				props_draw_column(arch->wall->props, arch, *pillar);
srcs/render/drawer/render_wall.c:114:		else if (arch->wall->status == PORTAL)
srcs/render/drawer/render_wall.c:122:		arch->px.x++;
srcs/render/drawer/render_wall.c:127:			sdl_MultiRenderCopy(arch->sdl);
srcs/render/drawer/render_wall.c:128:			SDL_RenderPresent(arch->sdl->rend);
srcs/render/drawer/render_wall.c:143:	len_sector = length_sector(player, arch->sector);
srcs/render/drawer/render_wall.c:144:	pillar_px = surface_pillar(arch, player, len_sector, arch->pillar.x);
srcs/render/drawer/render_wall.c:145:	next_px = surface_pillar(arch, player, len_sector, arch->next.x);
srcs/render/drawer/render_wall.c:146:	prop_iter_v(arch->wall->props, arch->wall->nb_props, &prop_init_render, arch);
srcs/render/drawer/render_wall.c:149:		if (arch->wall->status == PORTAL)
srcs/render/drawer/render_wall.c:151:		else if (arch->wall->status == WALL)
srcs/render/drawer/render_wall.c:155:	if (arch->wall->status == PORTAL)
srcs/render/drawer/render_wall.c:158:			printf("borne_svg(%d) %d %d\n", arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
srcs/render/drawer/render_wall.c:160:		px_draw = arch->px;
srcs/render/drawer/render_wall.c:161:		//start = arch->px.x;
srcs/render/drawer/render_wall.c:164:	if (arch->wall->status == PORTAL)
srcs/render/drawer/render_wall.c:166:		arch->px.x = px_draw.x;
srcs/render/drawer/render_wall.c:168:		arch->portal.pillar = arch->pillar;
srcs/render/drawer/render_wall.c:169:		arch->portal.next = arch->next;
srcs/render/drawer/render_wall.c:170:		sector_tmp = arch->sector;
srcs/render/drawer/render_wall.c:171:		arch->depth_portal++;
srcs/render/drawer/render_wall.c:173:			printf("borne(%d-->%d) %d %d\n", arch->depth_portal - 1, arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
srcs/render/drawer/render_wall.c:175:		sector_render(arch, player, arch->wall->link);
srcs/render/drawer/render_wall.c:176:		arch->depth_portal--;
srcs/render/drawer/render_wall.c:177:		arch->sector = sector_tmp;
srcs/render/drawer/render_wall.c:180:			printf("borne_load(%d) %d %d\n\n", arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
srcs/render/drawer/render_wall.c:192:	//if (arch->wall->status == CLOSE_DOOR || arch->wall->status == OPEN_DOOR)
srcs/render/drawer/render_wall.c:194:	//	door_split(arch, player, arch->wall->status);
srcs/render/drawer/render_wall.c:198:	if (arch->depth_portal == 0|| (wall_behind_portal(arch)))
srcs/render/drawer/render_wall.c:200:		if (arch->wall->status == CLOSE_DOOR || arch->wall->status == OPEN_DOOR)
srcs/render/drawer/render_wall.c:202:			door_split(arch, player, arch->wall->status);
srcs/render/drawer/textures.c:24:	px_affine.a = ((arch->sdl->size.x / 2) - arch->px.x) / arch->cam->d_screen;
srcs/render/drawer/textures.c:26:	if (arch->pillar.y == arch->next.y)
srcs/render/drawer/textures.c:28:		inter.x = arch->next.x;
srcs/render/drawer/textures.c:30:		percent = (inter.y - arch->pillar.y) / (arch->next.y - arch->pillar.y);
srcs/render/drawer/textures.c:34:		wall_affine.a = (arch->next.y - arch->pillar.y) / (arch->next.x - arch->pillar.x);
srcs/render/drawer/textures.c:35:		wall_affine.b = arch->pillar.y - wall_affine.a * arch->pillar.x;
srcs/render/drawer/textures.c:37:		percent = (inter.x - arch->pillar.x) / (arch->next.x - arch->pillar.x);
srcs/render/drawer/textures.c:39:	percent = percent * (arch->shift_txtr.y -  arch->shift_txtr.x) + arch->shift_txtr.x;
srcs/render/drawer/textures.c:85:		percent = &arch->shift_txtr.x;
srcs/render/drawer/textures.c:86:		pillar = &arch->pillar;
srcs/render/drawer/textures.c:90:		percent = &arch->shift_txtr.y;
srcs/render/drawer/textures.c:91:		pillar = &arch->next;
srcs/render/drawer/textures.c:93:	if (arch->pillar.x == arch->next.x)
srcs/render/drawer/textures.c:94:		percent_tmp = (inter.y - arch->pillar.y) / (arch->next.y - arch->pillar.y);
srcs/render/drawer/textures.c:96:		percent_tmp = (inter.x - arch->pillar.x) / (arch->next.x - arch->pillar.x);
srcs/render/drawer/textures.c:97:	*percent = percent_tmp * (arch->shift_txtr.y - arch->shift_txtr.x) + arch->shift_txtr.x;
srcs/render/pre_render/backface.c:14:	if (len_pillar > arch->portal.zline[px])
srcs/render/pre_render/backface.c:16:		arch->portal.zline[px] = len_pillar;
srcs/render/pre_render/backface.c:25:	if (len_pillar > arch->portal.zline[px])
srcs/render/pre_render/backface.c:27:		arch->portal.zline[px] = 0;
srcs/render/pre_render/backface.c:41:	if (len_pillar > arch->portal.zline[arch->px.x])
srcs/render/pre_render/backface.c:43:		zline_tmp[arch->px.x - start] = len_pillar;
srcs/render/pre_render/backface.c:44:		arch->portal.zline[arch->px.x] = 0;
srcs/render/pre_render/backface.c:47:	zline_tmp[arch->px.x - start] = arch->portal.zline[arch->px.x];
srcs/render/pre_render/backface.c:62:	while (start < arch->px.y)
srcs/render/pre_render/backface.c:64:		arch->portal.zline[start] = zline_cut[i];
srcs/render/pre_render/backface.c:73:	return (len_pillar > arch->portal.zline[px]);
srcs/render/pre_render/borne.c:15:	arch->portal.b_up[i] = (uint32_t)trunc_int(surface.x, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
srcs/render/pre_render/borne.c:16:	arch->portal.b_down[i] = (uint32_t)trunc_int(surface.y, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
srcs/render/pre_render/borne.c:21:	arch->portal.b_left = atan2((arch->sdl->size.x / 2) - arch->px.x, arch->cam->d_screen);
srcs/render/pre_render/borne.c:22:	arch->portal.b_right = atan2((arch->sdl->size.x / 2) - arch->px.y, arch->cam->d_screen);
srcs/render/pre_render/borne.c:23:	arch->portal.b_left *= TOANGLE;
srcs/render/pre_render/borne.c:24:	arch->portal.b_right *= TOANGLE;
srcs/render/pre_render/borne.c:35:	len = arch->px.y - arch->px.x;
srcs/render/pre_render/borne.c:36:	borne->b_left = arch->portal.b_left;
srcs/render/pre_render/borne.c:37:	borne->b_right = arch->portal.b_right;
srcs/render/pre_render/borne.c:40:	//----borne->decal_portal = arch->portal.decal_portal;
srcs/render/pre_render/borne.c:41:	//----borne->depth_portal = arch->portal.depth_portal;
srcs/render/pre_render/borne.c:43:	borne->pillar = arch->portal.pillar;
srcs/render/pre_render/borne.c:44:	borne->next = arch->portal.next;
srcs/render/pre_render/borne.c:58:	arch->portal.b_left = borne->b_left;
srcs/render/pre_render/borne.c:59:	arch->portal.b_right = borne->b_right;
srcs/render/pre_render/borne.c:64:		printf("start load start %d arch->px.y %d archmid %d\n", px_draw.x, arch->px.y, arch->sdl->size.x/2);
srcs/render/pre_render/borne.c:68:		arch->portal.b_up[px_draw.x] = borne->b_up[i];
srcs/render/pre_render/borne.c:69:		arch->portal.b_down[px_draw.x] = borne->b_down[i];
srcs/render/pre_render/borne.c:70:		arch->portal.zline[px_draw.x] = borne->zline[i];
srcs/render/pre_render/borne.c:74:	//-----arch->portal.decal_portal = borne->decal_portal;
srcs/render/pre_render/borne.c:75:	//-----arch->portal.depth_portal = borne->depth_portal;
srcs/render/pre_render/borne.c:76:	arch->portal.pillar = borne->pillar;
srcs/render/pre_render/borne.c:77:	arch->portal.next = borne->next;
srcs/render/pre_render/bunch.c:12:	if (arch->wall && (pillar == arch->wall->pillar || pillar == arch->wall->next))
srcs/render/pre_render/bunch.c:25:	if (angle >= arch->portal.b_right && angle <= arch->portal.b_left)
srcs/render/pre_render/bunch.c:53:	if (arch->portal.b_left * arch->portal.b_right > 0)
srcs/render/pre_render/bunch.c:89:	angles.x = local_angle(arch->portal.b_left, wall->pillar->angle);
srcs/render/pre_render/bunch.c:90:	angles.y = local_angle(arch->portal.b_left, wall->next->angle);
srcs/render/pre_render/bunch.c:135:			&& equal_pillar(&wall[i_wall], arch->wall))
srcs/render/pre_render/bunch.c:141:			&& equal_pillar(&wall[i_wall], arch->wall))
srcs/render/pre_render/bunch.c:149:		printf("deep_portal %d i_bunch %d\n", arch->depth_portal, i_bunch);
srcs/render/pre_render/bunch.c:159:	arch->sector = sector;
srcs/render/pre_render/bunch.c:162:		arch->wall = bunch[i];
srcs/render/pre_render/pillar_info.c:15:	angle.x = local_angle(arch->portal.b_left, arch->wall->pillar->angle);
srcs/render/pre_render/pillar_info.c:16:	angle.y = local_angle(arch->portal.b_left, arch->wall->next->angle);
srcs/render/pre_render/pillar_info.c:19:	polarite = (arch->wall->next->angle > arch->portal.b_left ? -1 : 1) * (diff < 180 ? 1 : -1);
srcs/render/pre_render/pillar_info.c:20:	arch->px.x = (polarite == -1) ? 0 : arch->sdl->size.x -1;
srcs/render/pre_render/pillar_info.c:21:	arch->px.y = arch->sdl->size.x - 1 - arch->px.x;
srcs/render/pre_render/pillar_info.c:30:	angle = local_angle(arch->portal.b_left, pillar->angle);
srcs/render/pre_render/pillar_info.c:31:	angle_next = local_angle(arch->portal.b_left, next->angle);
srcs/render/pre_render/pillar_info.c:32:	borne = local_angle(arch->portal.b_left, arch->portal.b_right);
srcs/render/pre_render/pillar_info.c:38:		return (arch->sdl->size.x - 1);
srcs/render/pre_render/pillar_info.c:42:		return (arch->sdl->size.x - 1);
srcs/render/pre_render/pillar_info.c:51:	size = arch->sdl->size.x;
srcs/render/pre_render/pillar_info.c:52:	if (arch->wall->pillar->frust)
srcs/render/pre_render/pillar_info.c:54:		arch->px.x = fish_bowl_px(arch, *arch->wall->pillar);
srcs/render/pre_render/pillar_info.c:55:		arch->pillar.x = distance(*(t_fvct2*)&p->stat.pos, arch->wall->pillar->p);
srcs/render/pre_render/pillar_info.c:56:		arch->pillar.y = sin(arch->wall->pillar->angle * PI180) * arch->pillar.x;
srcs/render/pre_render/pillar_info.c:57:		arch->pillar.x = cos(arch->wall->pillar->angle * PI180) * arch->pillar.x;
srcs/render/pre_render/pillar_info.c:58:		arch->shift_txtr.x = 1;
srcs/render/pre_render/pillar_info.c:62:		arch->px.x = pillar_polarite(arch, arch->wall->pillar, arch->wall->next);
srcs/render/pre_render/pillar_info.c:63:		if (arch->px.x == 0)
srcs/render/pre_render/pillar_info.c:65:			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->portal.b_left * PI180) * arch->cam->d_screen);
srcs/render/pre_render/pillar_info.c:66:			angle = p->stat.rot.y + arch->portal.b_left;
srcs/render/pre_render/pillar_info.c:70:			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->portal.b_right * PI180) * arch->cam->d_screen);
srcs/render/pre_render/pillar_info.c:71:			angle = p->stat.rot.y + arch->portal.b_right;
srcs/render/pre_render/pillar_info.c:73:		arch->shift_txtr.x = wall_clipping(arch, p, &tmp, angle);
srcs/render/pre_render/pillar_info.c:74:		arch->pillar = tmp;
srcs/render/pre_render/pillar_info.c:76:	if (arch->wall->next->frust)
srcs/render/pre_render/pillar_info.c:78:		arch->px.y = fish_bowl_px(arch, *arch->wall->next);
srcs/render/pre_render/pillar_info.c:79:		arch->next.x = distance(*(t_fvct2*)&p->stat.pos, arch->wall->next->p);
srcs/render/pre_render/pillar_info.c:80:		arch->next.y = sin(arch->wall->next->angle * PI180) * arch->next.x;
srcs/render/pre_render/pillar_info.c:81:		arch->next.x = cos(arch->wall->next->angle * PI180) * arch->next.x;
srcs/render/pre_render/pillar_info.c:83:		arch->shift_txtr.y = 0;
srcs/render/pre_render/pillar_info.c:87:		arch->px.y = pillar_polarite(arch, arch->wall->next, arch->wall->pillar);
srcs/render/pre_render/pillar_info.c:88:		if (arch->px.y == 0)
srcs/render/pre_render/pillar_info.c:90:			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->portal.b_left * PI180) * arch->cam->d_screen);
srcs/render/pre_render/pillar_info.c:91:			angle = p->stat.rot.y + arch->portal.b_left;
srcs/render/pre_render/pillar_info.c:95:			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->portal.b_right * PI180) * arch->cam->d_screen);
srcs/render/pre_render/pillar_info.c:96:			angle = p->stat.rot.y + arch->portal.b_right;
srcs/render/pre_render/pillar_info.c:98:		arch->shift_txtr.y = wall_clipping(arch, p, &tmp, angle);
srcs/render/pre_render/pillar_info.c:99:		arch->next = tmp;
srcs/render/pre_render/pillar_info.c:119:	a_pillar.a = arch->pillar.y / arch->pillar.x;
srcs/render/pre_render/pillar_info.c:121:	a_pillar2.a = arch->next.y / arch->next.x;
srcs/render/pre_render/pillar_info.c:124:	if (arch->portal.pillar.x == arch->portal.next.x)
srcs/render/pre_render/pillar_info.c:127:		a_portal.b = arch->portal.pillar.x;
srcs/render/pre_render/pillar_info.c:132:		a_portal.a = (arch->portal.next.y - arch->portal.pillar.y) / (arch->portal.next.x - arch->portal.pillar.x);
srcs/render/pre_render/pillar_info.c:133:		a_portal.b = arch->portal.pillar.y - a_portal.a * arch->portal.pillar.x;
srcs/render/pre_render/pillar_info.c:137:	if (inter.x > arch->pillar.x && inter2.x > arch->next.x)
srcs/render/pre_render/pillar_info.c:139:	if (arch->pillar.x == arch->next.x)
srcs/render/pre_render/pillar_info.c:142:		a_wall.b = arch->pillar.x;
srcs/render/pre_render/pillar_info.c:147:		a_wall.a = (arch->next.y - arch->pillar.y) / (arch->next.x - arch->pillar.x);
srcs/render/pre_render/pillar_info.c:148:		a_wall.b = arch->pillar.y - a_wall.a * arch->pillar.x;
srcs/render/pre_render/pillar_info.c:150:	if (inter.x > arch->pillar.x)
srcs/render/pre_render/pillar_info.c:155:		a_pillar.a = arch->pillar.y / arch->pillar.x;
srcs/render/pre_render/pillar_info.c:157:		arch->px.x = arch->sdl->size.x / 2 - affine_val(a_pillar, arch->cam->d_screen);
srcs/render/pre_render/pillar_info.c:159:	else if (inter2.x > arch->next.x)
srcs/render/pre_render/pillar_info.c:164:		a_pillar.a = arch->next.y / arch->next.x;
srcs/render/pre_render/pillar_info.c:166:		arch->px.y = arch->sdl->size.x / 2 - affine_val(a_pillar, arch->cam->d_screen);
srcs/render/pre_render/render_effect.c:9:	sx = (arch->sdl->size.x / 2.0);
srcs/render/pre_render/render_effect.c:10:	px = sx - (tan(pillar.angle * PI180) * arch->cam->d_screen);
srcs/render/pre_render/render_effect.c:11:	if (px >= arch->sdl->size.x)
srcs/render/pre_render/render_effect.c:12:		px = arch->sdl->size.x - 1;
srcs/render/pre_render/wall.c:19:	diff.x = arch->wall->pillar->p.x - p->stat.pos.x;
srcs/render/pre_render/wall.c:20:	diff.y = arch->wall->pillar->p.y - p->stat.pos.y;
srcs/render/pre_render/wall.c:21:	diff2.x = arch->wall->next->p.x - p->stat.pos.x;
srcs/render/pre_render/wall.c:22:	diff2.y = arch->wall->next->p.y - p->stat.pos.y;
srcs/render/pre_render/wall.c:54:	percent_open = (arch->timestamp - arch->wall->ots) / ((double)DOOR_OPEN_TIME * 3);
srcs/render/pre_render/wall.c:55:	//printf("timestamp %d start %d DOOR_TIME %d\n", arch->timestamp, arch->wall->ots, DOOR_OPEN_TIME);
srcs/render/pre_render/wall.c:64:	inter.x = percent_open * (arch->next.x - arch->pillar.x) + arch->pillar.x;
srcs/render/pre_render/wall.c:65:	inter.y = percent_open * (arch->next.y - arch->pillar.y) + arch->pillar.y;
srcs/render/pre_render/wall.c:67:	tmp = arch->next;
srcs/render/pre_render/wall.c:68:	arch->next = inter;
srcs/render/pre_render/wall.c:69:	px_tmp = arch->px.y;
srcs/render/pre_render/wall.c:70:	arch->px.y = arch->sdl->size.x / 2 - ((arch->next.y / arch->next.x) * (arch->sdl->size.x / 2));
srcs/render/pre_render/wall.c:71:	arch->wall->status = WALL;
srcs/render/pre_render/wall.c:74:		fill_line_debug(arch, arch->sdl, (t_vct2){arch->px.x, arch->sdl->size.y / 2}, (t_vct2){arch->px.y, arch->sdl->size.y / 2}, 0xffffffff);
srcs/render/pre_render/wall.c:78:		b_point_debug(arch->next, RED);
srcs/render/pre_render/wall.c:81:	arch->next = tmp;
srcs/render/pre_render/wall.c:82:	arch->px.y = px_tmp;
srcs/render/pre_render/wall.c:83:	arch->wall->status = flag;
srcs/render/prop.c:82:	percent_wall.x = (prop->percent.x - (arch->shift_txtr.x)) / (arch->shift_txtr.y - arch->shift_txtr.x);
srcs/render/prop.c:83:	percent_wall.y = (prop->percent.y - (arch->shift_txtr.x)) / (arch->shift_txtr.y - arch->shift_txtr.x);
srcs/render/prop.c:84:	delta_wall.x = arch->next.x - arch->pillar.x;
srcs/render/prop.c:85:	delta_wall.y = arch->next.y - arch->pillar.y;
srcs/render/prop.c:86:	prop_left_pos.x = delta_wall.x * percent_wall.x + arch->pillar.x;
srcs/render/prop.c:87:	prop_left_pos.y = delta_wall.y * percent_wall.x + arch->pillar.y;
srcs/render/prop.c:88:	prop_rigth_pos.x = delta_wall.x * percent_wall.y + arch->pillar.x;
srcs/render/prop.c:89:	prop_rigth_pos.y = delta_wall.y * percent_wall.y + arch->pillar.y;
srcs/render/prop.c:90:	px_props.y = arch->sdl->size.x / 2 - ((prop_rigth_pos.y / prop_rigth_pos.x) * (arch->sdl->size.x / 2));
srcs/render/prop.c:91:	px_props.x = arch->sdl->size.x / 2 - ((prop_left_pos.y / prop_left_pos.x) * (arch->sdl->size.x / 2));
srcs/render/prop.c:104:		fill_line_debug(arch, arch->sdl, (t_vct2){px_props.x, arch->sdl->size.y / 2}, (t_vct2){px_props.y, arch->sdl->size.y / 2}, 0xffffffff);
srcs/render/prop.c:129:	heigth_percent.x = (arch->sector->h_ceil - 2) / arch->sector->h_ceil;
srcs/render/prop.c:130:	heigth_percent.y = 1 / arch->sector->h_ceil;
srcs/render/prop.c:131:	while (i < arch->wall->nb_props && !col_print)
srcs/render/prop.c:133:		if (arch->px.x > props[i].px.x && arch->px.x < props[i].px.y)
srcs/render/prop.c:141:			cursor = arch->px.x + surface_tmp.x * arch->sdl->size.x;
srcs/render/prop.c:143:				cursor = arch->px.x;
srcs/render/prop.c:144:			props[i].tex = &arch->sector->txtrtop;
srcs/render/render.c:30:		printf(WBLUE"\nrender_sector(%d) up %d down %d\n"WEND, arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
srcs/render/render.c:33:	if (debug_screen == 2 && arch->depth_portal > 0)
srcs/render/render.c:38:	arch->sector = sector;
srcs/render/render.c:39:	portal_tmp = arch->wall;
srcs/render/render.c:48:				&& equal_pillar(&wall[i], arch->wall))
srcs/render/render.c:50:			portal_tmp = arch->wall;
srcs/render/render.c:51:			arch->wall = &wall[i];
srcs/render/render.c:53:			arch->wall = portal_tmp;
srcs/render/render.c:60:		if (arch->depth_portal > 3)
srcs/render/render.c:63:			color[0] = color[arch->depth_portal];
srcs/render/render.c:68:		printf("render_enemy(%d) up %d down %d\n", arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
srcs/render/render_enemy.c:61:	surface.x = camera_proj_heigth(arch->cam, arch->sdl, player, len.x, depth);
srcs/render/render_enemy.c:62:	surface.y = camera_proj_heigth(arch->cam, arch->sdl, player, len.y, depth);
srcs/render/sprite.c:102:			posx = arch->sdl->size.x / 2 - sprite->pos.y / sprite->pos.x * arch->cam->d_screen;
srcs/render/sprite.c:103:			sprite->heigth = cam_get_enemy_surface(arch->cam, arch->sdl, enemy, player, sprite->pos.x);
srcs/render/sprite.c:129:			posx = arch->sdl->size.x / 2 - sprite->pos.y / sprite->pos.x * arch->cam->d_screen;
srcs/render/sprite.c:155:	neutral_distance = (double)(arch->sdl->size.y) / sprite->pos.x;
srcs/render/sprite.c:174:	if (sprite->width.y > arch->sdl->size.x)
srcs/render/sprite.c:175:		sprite->width.y = arch->sdl->size.x;
srcs/render/sprite.c:176:	if (sprite->heigth.y > arch->sdl->size.y)
srcs/render/sprite.c:177:		sprite->heigth.y = arch->sdl->size.y - 1;
srcs/render/sprite.c:182:			if (sprite->heigth.x < (int)arch->portal.b_up[sprite->width.x])
srcs/render/sprite.c:184:				i_heigth = (int)arch->portal.b_up[sprite->width.x];
srcs/render/sprite.c:185:				buffer_h = (arch->portal.b_up[sprite->width.x] - sprite->heigth.x) * p_buff_h;
srcs/render/sprite.c:192:			cursor_screen = sprite->width.x + (i_heigth * arch->sdl->size.x);
srcs/render/sprite.c:193:			if (sprite->heigth.y > (int)arch->portal.b_down[sprite->width.x])
srcs/render/sprite.c:194:				limit_h = arch->portal.b_down[sprite->width.x] * arch->sdl->size.x;
srcs/render/sprite.c:196:				limit_h = sprite->heigth.y * arch->sdl->size.x;
srcs/render/sprite.c:201:				arch->sdl->screen[cursor_screen] =
srcs/render/sprite.c:203:				cursor_screen += arch->sdl->size.x;
