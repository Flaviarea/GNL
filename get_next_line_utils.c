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
                ++len; // yes, you increse len, you want to include the newline 
                return (len);
            }
            ++i;
            ++len;
        }
        list = list->next; //it leads me to the final node
    }
    return (len);
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
        while (list->str_buf[i]) //until i have a char go into the loop
        {
            if (list->str_buf[i] == '\n') //check if the char pointed by i is n 
            {
                str[k++] = '\n'; //if yes, copy n and append zero 
                str[k] - '\0';
                return ;
            }
            str[k++] = list->str_buf[i++]; //if not, copy the string 
        }
        list = list->next; //go to the next node 
    }
    str[k] = '\0';
}
