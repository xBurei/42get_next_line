/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:57:12 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/18 13:00:16 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 20
#endif

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

    line_buf = malloc(sizeof(t_line_buf));
    if (!line_buf)
        return (NULL);
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

    if (rd_buf->rd_out == 0)
        return (0);
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

void    clear_rd_buf(t_rd_buf *rd_buf)
{
    size_t  i;

    i = 0;
    while (i < BUFFER_SIZE)
        rd_buf->content[i++] = 0;
    rd_buf->index = 0;
    rd_buf->rd_out = 0;
}

void append(t_line_buf *l_b, t_rd_buf *rd_b)
{
    int i;

    i = -1;
    if (nl_found(rd_b))
    {
        // copy until newline
        while (rd_b->content[rd_b->index + ++i] != '\n')
            l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
        l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
        i++;
        l_b->index += i;
        rd_b->index += i;
    }
    if (rd_b->rd_out != BUFFER_SIZE)
    {
        // copy until eof
        while (rd_b->content[rd_b->index + ++i] < rd_b->rd_out)
            l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
        l_b->index += i;
        rd_b->index += i;
        clear_rd_buf(rd_b);
    }
    else
    {
        resize_line_buf(l_b);
        while (rd_b->content[rd_b->index + ++i] < BUFFER_SIZE)
            l_b->content[l_b->index + i] = rd_b->content[rd_b->index + i];
        clear_rd_buf(rd_b);
    }
}

char *get_next_line(int fd)
{
    static t_rd_buf *rd_buf;
    t_line_buf      *line_buf;

    if (fd < 0)
        return (NULL);
    init_line_buf(line_buf);
    if (!line_buf)
        return (NULL);
    while (!nl_found(rd_buf) || rd_buf->rd_out != BUFFER_SIZE)
    {
        fill_read_buf(fd, rd_buf);
        append(line_buf, rd_buf);
    }
    return (line_buf->content);
}

int main()
{
    int fd;

    fd = open("testfile.txt", O_RDONLY, 0666);
    printf("%s", get_next_line(fd));
}