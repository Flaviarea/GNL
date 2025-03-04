/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:31 by frea              #+#    #+#             */
/*   Updated: 2025/02/24 18:46:33 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> // Necessario per open()

int main(void)
{
    int fd;
    char *line;
    
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
	{
		printf("Error opening the file, try again.\n");
		return (1);
	}
    printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
    while(1)
    {
        line = get_next_line(fd);
        printf("%s", line);
        if (line == NULL)
        {
            printf("%s", line);
            free(line);
            break;
        }
    }
    printf("\n");
	close(fd);
	return(0);
}
