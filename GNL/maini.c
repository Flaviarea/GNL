/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maini.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:31 by frea              #+#    #+#             */
/*   Updated: 2025/02/24 18:46:33 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;
	int		count;
	
	count = 1;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening the file, try again.\n");
		return (1);
	}
	// line = get_next_line(fd);
	// printf("line#%d --- %s",count++, line);
	// line = get_next_line(fd);
	// printf("line#%d --- %s",count++, line);
	// line = get_next_line(fd);
	// printf("line#%d --- %s",count++, line);
	// free(line);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	while(1)
	{
		line = get_next_line(fd);
		printf("line#%d --- %s", count++, line);
		if(line == NULL)
		{
			free(line);
			break;
		}
		free(line);
		line = NULL;
	}
	printf("\n");
	close(fd);
	return(0);
}
