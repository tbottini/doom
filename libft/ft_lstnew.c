/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:19 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:24:38 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_strdup(const char *s)
{
	size_t	x;
	char	*new;

	x = 0;
	while (s[x])
		x++;
	if (!(new = (char *)malloc(x * sizeof(char))))
		return (NULL);
	x = 0;
	while (s[x])
	{
		new[x] = s[x];
		x++;
	}
	new[x] = '\0';
	return (new);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*var;

	if (!(var = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	var->next = NULL;
	if (content == NULL)
	{
		var->content = NULL;
		var->content_size = 0;
		return (var);
	}
	var->content = new_strdup((char *)content);
	var->content_size = content_size;
	return (var);
}
