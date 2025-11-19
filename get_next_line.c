/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:23:52 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/19 15:29:26 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strdup(const char *str)
{
	size_t	strlen;
    size_t  i;
	char	*result;

	strlen = 0;
    while (str[strlen])
    {
        strlen++;
    }
	result = malloc(strlen + 1);
	if (!result)
		return (NULL);
    i = 0;
	while (i < strlen)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
	return (result);
}

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
    free(tmp);
    while ((size_t) ++i < line->capacity)
        line->content[i] = 0;
    return (line);
}

unsigned int    append(char *buffer, t_line *line, size_t rd_index, int rd_out)
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

char    *rd_til_nl_eof(int fd, char *b, t_line *l, size_t *rd_i, int *rd_o)
{
    char    *out;

    out = NULL;
    *rd_o = read(fd, b, BUFFER_SIZE);
    if (*rd_o <= 0)
    {
        if (l->index)
            return (l->content);
        return (NULL);
    }
    if (l->index + *rd_o > l->capacity)
        l = resize_line_buffer(l);
    if (!l)
        return (NULL);
    *rd_i = append(b, l, *rd_i, *rd_o);
    if ((l->index && l->content[l->index - 1] == '\n') || *rd_o < BUFFER_SIZE)
        out = ft_strdup(l->content);
    if (*rd_i >= (unsigned int) *rd_o)
    {
        *rd_o = 0;
        *rd_i = 0;
    }
    return (out);
}

char    *get_next_line(int fd)
{
    t_line                  *line;
    static char             buffer[BUFFER_SIZE];
    static size_t           rd_index = 0;
    static int              rd_out = 0;
    char                    *out;

    out = NULL;
    if (fd < 0)
        return (NULL);
    line = init_line_buf();
    if (!line)
        return (NULL);
    while (!out)
    {
        out = rd_til_nl_eof(fd, buffer, line, &rd_index, &rd_out);
        if (!out && !line->index)
            break;
    }
    free(line->content);
    free(line);
    return (out);
}

int main()
{
    int fd = open("testfile2.txt", O_RDONLY, 0666);
    char    *out;
    for (int i = 0; i < 103; i++)
    {
        out = get_next_line(fd);
        printf("%d : %s", i, out);
        if (out)
            free(out);
    }
}