
#ifndef DEBUG_H
# define DEBUG_H

# include "doom_struct.h"

t_wall					*chunck_walls(t_list *chunck_line, size_t len);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd);
t_fvct2					*double_atof(char *line, t_fvct2 *vct);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);

#endif
