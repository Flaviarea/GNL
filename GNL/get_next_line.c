/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:13 by frea              #+#    #+#             */
/*   Updated: 2025/02/24 18:46:16 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_list(t_list **list, int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
char	*get_line(t_list *list);
void	polish_list(t_list **list);
void	append(t_list **list, char *buf);
char	*get_next_line(int fd);

/*
    Polish linked list for next call
*/

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

/*
	get_line:
	input: the list with all the nodes
	next_str = to store the small strings 
	read by buff of create_list in one bigger string
	Output: the line until the /n
*/

char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc (str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

/* To append one node to the next of the list*/

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

/*
    create_list:
    to read the file in blocks of BUFFER_SIZE per time.
    creates nodes to append to the linked lists until it find a \n
    buf = temporary buf with BUFFER_SIZE byted read inside
*/

void	create_list(t_list **list, int fd)
{
	ssize_t	char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return ;
		char_read = read (fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

/*  
    get_next_line:
    Input: int file descriptor
    next_line = to store the return value of get_line
    Output: next_str (return value of of get_line) 
*/

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}
