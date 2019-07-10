#include "doom_nukem.h"

t_list		*list_chunk_line(int fd, uint32_t *nline)
{
	char		*line;
	t_list		*start;
	t_list		*cursor;


	*nline = 0;
	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "END"))
	{
		if (*nline == 0)
		{
			start = ft_lstn(line);
			if (!start)
				return (NULL);
			cursor = start;
		}
		else
		{
			cursor->next = ft_lstn(line);
			if (!cursor->next)
				return (NULL);
			cursor = cursor->next;
		}
		(*nline)++;
	}
	free(line);
	return (start);
}
/*
int			chunk_texture(t_sdl *sdl, t_arch *designer, int fd)
{
	t_list		*file_list;
	void		*tmp;
	uint32_t	size;
	uint32_t	i;

	file_list = list_chunk_line(fd, &size);
	if (!file_list)
		return (0);
	designer->texture = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * (size + 1));
	if (!designer->texture)
		return (0);
	designer->texture[size] = NULL;
	i = 0;
	while (i < size)
	{
		tmp = IMG_Load((char*)file_list->content);
		if (!tmp)
			return (0);
		designer->texture[i] = SDL_ConvertSurface((SDL_Surface*)tmp, sdl->format, 0);
		if (!designer->texture[i])
			return (0);
		SDL_FreeSurface((SDL_Surface*)tmp);
		tmp = file_list;
		file_list = file_list->next;
		free(((t_list*)tmp)->content);
		free(tmp);
		i++;
	}
	return (1);
}
*/
