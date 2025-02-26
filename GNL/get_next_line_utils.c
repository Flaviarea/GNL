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
    int i; // Variabile per iterare all'interno del buffer di ogni nodo della lista,  Contatore che scorrerà i caratteri nel buffer dei nodi.

    if (NULL == list)
        return (0);
    while (list)
    {
        i = 0; // riparti sempre da zero per ogni nodo della lista 
        while (list->str_buf[i] && i < BUFFER_SIZE)
        {
            if (list->str_buf[i] == '\n')
                return (1);
                ++i;
        }
        list = list->next; //passa al nodo successivo
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
// Conta quanti caratteri ci sono fino al \n (incluso), così sappiamo quanto spazio allocare.
// Conta carattere per carattere fino a trovare \n o terminare la lista.
// Restituisce la lunghezza esatta della linea, incluso \n.

int len_to_newline(t_list *list)
{
    int i; //Iteratore per scorrere i caratteri nel nodo
    int len; //Conta il numero totale di caratteri fino al \n.

    if (NULL == list)
        return (0);
    len = 0;

    while (list)
    {
        i = 0;
        while (list->str_buf[i]) // while the char inside the string of the node is not zero, Scorre i caratteri nel buffer del nodo corrente
        {
            if (list->str_buf[i] == '\n') //check if the char is the newline, Se trova \n, lo conta e termina
            {
                ++len; // yes, you prefix-increse len, you want to include the newline , Conta anche il \n
                return (len);
            }
            ++i;
            ++len; //Aggiunge il carattere alla lunghezza
        }
        list = list->next; //it leads me to the next node
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

