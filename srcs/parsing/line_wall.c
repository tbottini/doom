#include "doom_nukem.h"

int				line_wall(t_arch *rsrc, t_wall *wall, char *line)
{
	int			txtr_index;

	if (line[0] == 'W')
		wall->status = WALL;
	else if (line[0] == 'O')
		wall->status = WINDOW;
	else if (line[0] == 'P')
		wall->status = PORTAL;
	//else
	//	return (0);
	printf("line %s\n", line);
	line = double_atof(line, &wall->pillar->p);
	//line = double_afo
	txtr_index = atoi(line);
	printf("%d txtr_index\n", txtr_index);
	wall->txtr.pixels = rsrc->texture[txtr_index]->pixels;
	wall->txtr.w = rsrc->texture[txtr_index]->w;
	wall->txtr.h = rsrc->texture[txtr_index]->h;
	return (1);
}
