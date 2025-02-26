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

int found_newline(t_list *list)
{
    int i;

    if (NULL == list)
        return (0);
    while (list)
    {
        i = 0;
        while (list->str_buf[i] && i < BUFFER_SIZE)
        {
            if (list->str_buf[i] == '\n')
                return (1);
                ++i;
        }
        list = list->next;
    }
    return (0);
}

t_list  *find_last_node(t_list *list)
{
    if (NULL == list)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

void    copy_str(t_list *list, char *str)
{
    int i;
    int k;

    if (NULL == list)
        return;
    k = 0;
    while (list)
    {
        i = 0;
        while (list->str_buf[i]) //until i have a char, step into the loop
        {
            if (list->str_buf[i] == '\n') //check if the char pointed by i is \n 
            {
                str[k++] = '\n'; //if yes, copy n and append \zero 
                str[k] - '\0';
                return ;
            }
            str[k++] = list->str_buf[i++]; //if not, copy the string 
        }
        list = list->next; //go to the next node 
    }
    str[k] = '\0';
}

// find the len to new line in the linked list

int len_to_newline(t_list *list)
{
    int i;
    int len;

    if (NULL == list)
        return (0);
    len = 0;

    while (list)
    {
        i = 0;
        while (list->str_buf[i]) // while the char inside the string of the node is not zero
        {
            if (list->str_buf[i] == '\n') //check if the char is the newline 
            {
                ++len; // yes, you prefix-increse len, you want to include the newline 
                return (len);
            }
            ++i;
            ++len;
        }
        list = list->next; //it leads me to the final node
    }
    return (len);
}

// dealloc all, set heat to NULL

void dealloc(t_list **list, t_list *clean_node, char *buf)
{
    t_list *tmp;

    if (NULL == *list)
        return ;
    while(*list)
    {
        tmp = (*list)->next;
        free(*list)->str_buf;
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (clean_node->str_buf[0])
        *list = clean_node;
    else
    {
        free(buf);
        free(clean_node);
    }
}

