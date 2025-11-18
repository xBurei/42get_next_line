/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:57:12 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/18 12:13:33 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

t_line_buf *resize_line_buf(t_line_buf *line_buf)
{
    int i;
    char *tmp;

    tmp = malloc(line_buf->capacity);
    if (!tmp)
        return (NULL);
    i = -1;
    while (++i <= line_buf->index)
        tmp[i] = line_buf->content[i];
    free(line_buf->content);
    line_buf->content = malloc(line_buf->capacity * 2);
    if (!line_buf->content)
        return (NULL);
    i = -1;
    while (++i <= line_buf->index)
        line_buf->content[i] = tmp[i];
    line_buf->capacity *= 2;
    while (i <= line_buf->index)
        line_buf->content[i++] = 0;
    return (line_buf);
}

t_line_buf *init_line_buf(t_line_buf *line_buf)
{
    size_t i;

    line_buf->content = malloc(BUFFER_SIZE);
    if (!line_buf->content)
        return (NULL);
    i = 0;
    while (i < BUFFER_SIZE)
        line_buf->content[i++] = 0;
    line_buf->index = 0;
    line_buf->capacity = BUFFER_SIZE;
    return (line_buf);
}

int nl_found(t_rd_buf *rd_buf)
{
    size_t i;

    i = 0;
    while (rd_buf->index + i < rd_buf->rd_out)
    {
        if (rd_buf->content[i++] == '\n')
            return (1);
    }
    return (0);
}

int fill_read_buf(int fd, t_rd_buf *rd_buf)
{
    rd_buf->rd_out = read(fd, rd_buf->content, BUFFER_SIZE);
    if (rd_buf->rd_out >= 0)
        return (0);
}

void append(t_line_buf *l_b, t_rd_buf *rd_b)
{
    size_t i;

    if (nl_found(rd_b->content))
    {
        // copy until newline
        i = 0;
        while (rd_b->content[rd_b->index + i] != '\n')
        {
            l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
            i++;
        }
        l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
        i++;
        l_b->index += i;
        rd_b->index += i;
    }
    if (rd_b->rd_out != BUFFER_SIZE)
    {
        // copy until eof
    }
    else
    {
        // resize_line_buf
    }
}

char *get_next_line(int fd)
{
    static t_rd_buf *rd_buf;
    t_line_buf *line_buf;

    if (fd < 0)
        return (NULL);
    line_buf = init_line_buf(line_buf);
    if (!line_buf)
        return (NULL);
}