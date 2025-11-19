/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:23:52 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/19 11:54:58 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_line  *init_line_buf(t_line *l)
{
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

unsigned int    get_nl_index(char *buf, unsigned int rd_index, int rd_out)
{
    size_t  i;

    i = 0;
    while (buf[i + rd_index] != '\n' && i + rd_index < rd_out)
        i++;
    return (i + rd_index);
}

t_line      *resize_line_buffer(t_line *line)
{
    char    *tmp;
    int     i;
            
    tmp = malloc(line->capacity + 1);
    if (!tmp)
        return (NULL);
    i = -1;
    while (++i < line->index)
        tmp[i] = line->content[i];
    free(line->content);
    line->content = malloc(line->capacity * 2 + 1);
    if (!line->content)
        return (NULL);
    line->capacity *= 2;
    i = -1;
    while (++i < line->index)
        line->content[i] = tmp[i];
    while (++i < line->capacity)
        line->content[i] = 0;         
    return (line);
}

unsigned int    append(char *buffer, t_line *line, unsigned int rd_index, int rd_out)
{
    int  i;
    
    i = -1;
    while (rd_index + ++i < rd_out)
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
    line = init_line_buf(line);
    if (!line)
        return (NULL);
    while (rd_out > 0)
    {
        rd_index = append(buffer, line, rd_index, rd_out);
        /* printf("line index : %u\n",line->index);
        printf("rd index %u\n", rd_index);
        printf("rd out %u\n", rd_out); */
        if (rd_index >= rd_out)
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
            return (NULL);
        if (line->index + rd_out > line->capacity)
            line = resize_line_buffer(line);
        if (!line)
            return (NULL);
        rd_index = append(buffer, line, rd_index, rd_out);
        if (line->index && line->content[line->index - 1] == '\n')
            return (line->content);
        if (rd_index >= rd_out)
        {
            rd_out = 0;
            rd_index = 0;
        }
    }
}

int main()
{
    int fd = open("testfile.txt", O_RDONLY, 0666);
    for (int i = 0; i < 101; i++)
        printf("%d : %s", i, get_next_line(fd));
}