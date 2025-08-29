/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:54 by frea              #+#    #+#             */
/*   Updated: 2025/08/26 14:32:58 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1];
	char		*ret = NULL;
	char		*nl;
	int			read_ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		nl = ft_strchr(b, '\n');
		if (nl)
		{
			if (!str_append_mem(&ret, b, nl - b + 1))
				return (free(ret), NULL);
			ft_memcpy(b, nl + 1, ft_strlen(nl + 1) + 1);
			return (ret);
		}
		if (!str_append_str(&ret, b))
			return (free(ret), NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
		    free(ret);
		    b[0] = '\0';      // svuota il buffer statico
		    return (NULL);
		}
		if (read_ret == 0)
		{
		    b[0] = '\0';
		    if (ret && *ret)
			return (ret);
		    return (free(ret), NULL);
		}
		b[read_ret] = '\0';
	}
}


