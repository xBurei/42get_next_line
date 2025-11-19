/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:20:19 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/19 10:02:19 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_line {
    char            *content;
    size_t          size;
    size_t          capacity;
    unsigned int    index;
} t_line;

typedef struct s_rd_metadata {
    unsigned int    rd_start;
    unsigned int    rd_stop;
    int             rd_out;
} t_rd_metadata;

#endif