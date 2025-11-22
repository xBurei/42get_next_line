/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:20:19 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/22 14:38:21 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char    *get_next_line(int fd);

typedef struct s_line {
    char            *content;
    size_t          size;
    size_t          capacity;
}   t_line;

typedef struct s_rd {
    char    buf[BUFFER_SIZE + 1];
    size_t     start;
    size_t     end;
    int     o;
}   t_rd;

#endif