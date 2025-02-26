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
#include <stdlib.h>
#include <stdio.h>

void    create_list(t_list **list, int fd);
void dealloc(t_list **list, t_list *clean_node, char *buf);
char    *get_line(t_list *list);
void    polish_list(t_list **list);

// Return value: next_line

char *get_next_line(int fd)
{
    static t_list   *list; //Dichiarazione di una lista concatenata statica, che mantiene il contenuto tra più chiamate alla funzione.
    char    *next_line; //stock the next line i'm taking, the little buffer (return)

    list = NULL; /////errore

    // fd only can be positive | read gives -1 if some problems while reading) | if you have the permissions to open the file 
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return (NULL);

    //create my list till I stumble into \n
    create_list(&list, fd); // chiama la funzione create per leggere il file e costruire la lista concatenata 

    if (list == NULL)
        return (NULL);

    //recupera the line from the list
    next_line = get_line(list); // Recupera la riga completa dalla lista concatenata in the heap

    polish_list(&list); // "Pulisce" la lista concatenata eliminando la riga già restituita.
    return (next_line);
}

char    *get_line(t_list *list)
{
    int str_len; // Lunghezza della stringa da allocare, Memorizza la lunghezza della riga fino al \n (compreso).
    char    *next_str; //Puntatore alla stringa che verrà restituita, Verrà allocata dinamicamente per contenere la riga estratta.

    if (NULL == list)
        return (NULL);

    // count how many char are until the \n, so i know how much to malloc
    str_len = len_to_newline(list); //Conta quanti caratteri ci sono fino al \n
    next_str = malloc(str_len + 1);
    if (NULL == next_str)
        return (NULL);

    // copy the stirng into the buffer and return it 
    copy_str(list, next_str);
    return (next_str); //Ritorna la stringa con la linea estratta
}

// append one node to the end of the list

void append(t_list **list, char *buf)
{
    t_list  *new_node; // Il nuovo nodo da aggiungere alla lista.
    t_list  *last_node; // Ultimo nodo attuale della lista.

    last_node = find_last_node(*list); //Trova l'ultimo nodo della lista.
    new_node = malloc(sizeof(t_list));
    if (NULL == new_node)
        return ;

    //if the list is empy, if NULL == *list
    // then assign to list the value of new_node
    if (NULL == last_node) //Se la lista è vuota (NULL), il nuovo nodo diventa il primo nodo.
        *list = new_node;
    else
        last_node->next = new_node; //Altrimenti, lo collega all’ultimo nodo esistente.

    new_node->str_buf = buf; //Salva il buffer nel nuovo nodo e lo mette in coda alla lista.
    new_node->next = NULL;
}

// Legge il file a blocchi di BUFFER_SIZE caratteri alla volta.
// Crea nodi nella lista concatenata fino a trovare un \n.

void    create_list(t_list **list, int fd)
{
    int char_read; // Tiene traccia di quanti caratteri sono stati letti
    char *buf; //memorizza i caratteri letti, stock my string in buf, a spot in memory in the heap

    //dobbiamo recuperare la stringa fino alla \n inclusa quindi cerca dentro la lista se c'e una newline
    // se non trovi una nuova linea entra nel loop 
    while(!found_newline(*list)) //Ciclo che continua a leggere finché non trova un \n.
    {
        buf = malloc(BUFFER_SIZE + 1); // plus null terminator 
        if (NULL == buf)
            return;

            char_read = read(fd, buf, BUFFER_SIZE); // Legge BUFFER_SIZE caratteri dal file e li memorizza in buf.
            if (!char_read) // if the number of char is zero (char_read) then return == i finished the file 
            {
                free(buf); // it means i have finished the file 
                return;
            }
            buf[char_read] = '\0'; //append zero at the end
            // append the node 
            append(list, buf); //Aggiunge buf alla lista concatenata
    }
}

// polish linked list for the next call 

void    polish_list(t_list **list)
{
    t_list  *last_node;
    t_list  *clean_node;
    int i; //Indice per scorrere last_node->str_buf.
    int k; //Indice per riempire il nuovo buffer buf.
    char *buf;

    buf = malloc(BUFFER_SIZE + 1) // in the buffer i will put the last chars of the last node
    clean_node = malloc(sizeof(t_list));
    if (NULL == buf || NULL == clean_node)
    return ;
    last_node = find_last_node(*list); //search for the last node 

    i = 0;
    k = 0;
    while (last_node->str_buf[i] != '\0'   //skip all the chars I dont need
        && last_node->str_buf[i] != '\n')
        ++i; //salta i caratteri gia letti 

    while (last_node->str_buf[i] != '\0'
        && last_node->str_buf[++i]) //you can have file that have no newline
        buf[k++] = last_node->str_buf[i];
    buf[k] = '\0';
    clean_node->str_buf = buf; // assign to my string the new buffer 
    clean_node->next = NULL;
    dealloc(list, clean_node, buf);
}

int main()
{
    int fd;
    char *line;
    int lines;

    lines = 1;
    fd = open("test.txt", O_RDONLY);

    while (line = get_next_line(fd))
        prinf("d->%s\n", list++, line);
}