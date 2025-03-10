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
#include <fcntl.h>

/*int main(void)
{
    int fd;
    char *line;
    
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
	{
		printf("Error.\n");
		return (1);
	}
    while(1)
    {
        line = get_next_line(fd);
    if (line)
    printf("%s", line);
       if (!line)
        {
            free(line);
            break;
        }
    }
    	    free(line);
	close(fd);
	return(0);
}
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error.\n");
        return (1);
    }

    while (1)
    {
        line = get_next_line(fd); 

        if (!line) 
        {
            break;
        }
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}

