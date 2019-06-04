#include "doom_nukem.h"

int			open_writable(char filename)
{
	return(open(filename, O_CREAT | O_WRONLY, 0777));
}

void		write_signature(int fd)
{
	//4 octets 56.781.334.1

}

void		write_sector(int fd, t_sector sector)
{

}

void		write_player(int fd, t_player player)
{

}

int			write_map(char filename)
{
	int		fd;

	fd = open_writable(filename);
	if (fd == -1)
		return (0);

	return (1);
}