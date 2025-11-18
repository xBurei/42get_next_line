/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:20:19 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/18 09:58:22 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

typedef struct s_rd_buffer
{
    char content[BUFFER_SIZE];
    size_t index;
    int rd_out;
} t_rd_buf;

typedef struct s_line_buffer
{
    char *content;
    size_t index;
    size_t capacity;
} t_line_buf;

#endif
