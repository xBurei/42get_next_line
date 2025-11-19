/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:23:52 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/19 12:47:28 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_line  *init_line_buf()
{
    t_line *l;
    
    l = malloc(sizeof(t_line));
    if (!l)
        return (NULL);
    l->content = malloc(BUFFER_SIZE + 1);
    if (!l->content)
        return (NULL);
    l->capacity = BUFFER_SIZE;
    l->index = 0;
    l->size = 0;
    return (l);
}

t_line      *resize_line_buffer(t_line *line)
{
    char    *tmp;
    int     i;
            
    tmp = malloc(line->capacity + 1);
    if (!tmp)
        return (NULL);
    i = -1;
    while ((size_t) ++i < line->index)
        tmp[i] = line->content[i];
    free(line->content);
    line->content = malloc(line->capacity * 2 + 1);
    if (!line->content)
        return (NULL);
    line->capacity *= 2;
    i = -1;
    while ((size_t) ++i < line->index)
        line->content[i] = tmp[i];
    while ((size_t) ++i < line->capacity)
        line->content[i] = 0;         
    return (line);
}

unsigned int    append(char *buffer, t_line *line, unsigned int rd_index, int rd_out)
{
    int  i;
    
    i = -1;
    while ((int) rd_index + ++i < rd_out)
    {
        line->content[line->index + i] = buffer[rd_index + i];
        if (line->content[line->index + i] == '\n')
        {
            ++i;
            break ;
        }
    }
    line->content[line->index + i] = '\0';
    line->index += i;
    return (rd_index + i);
}

char    *get_next_line(int fd)
{
    t_line                  *line;
    static char             buffer[BUFFER_SIZE];
    static unsigned int     rd_index = 0;
    static int              rd_out = 0;

    if (fd < 0)
        return (NULL);
    line = init_line_buf();
    if (!line)
        return (NULL);
    while (rd_out > 0)
    {
        rd_index = append(buffer, line, rd_index, rd_out);
        if (rd_index >= (unsigned int) rd_out)
        {
            rd_out = 0;
            rd_index = 0;
        }
        if (line->index && line->content[line->index - 1] == '\n')
            return (line->content);
    }
    while (rd_out <= 0)
    {
        rd_out = read(fd, buffer, BUFFER_SIZE);
        if (rd_out <= 0)
        {
            if (line->index)
                return (line->content);
            return (NULL);
        }
        if (line->index + rd_out > line->capacity)
            line = resize_line_buffer(line);
        if (!line)
            return (NULL);
        rd_index = append(buffer, line, rd_index, rd_out);
        if ((line->index && line->content[line->index - 1] == '\n') || rd_out < BUFFER_SIZE)
            return (line->content);
        if (rd_index >= (unsigned int) rd_out)
        {
            rd_out = 0;
            rd_index = 0;
        }
    }
    return (line->content);
}

/* int main()
{
    int fd = open("testfile3.txt", O_RDONLY, 0666);
    for (int i = 0; i < 1800; i++)
        printf("%d : %s", i, get_next_line(fd));
} */