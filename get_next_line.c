/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:20:23 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/15 15:43:41 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

void	ft_bzero(void *ptr, size_t n)
{
    size_t c;
    
	c = 0;
	while (c < n)
		*(unsigned char *)(ptr + c++) = 0;
}

size_t	write_to_output(char *rd_buf, char **out, size_t offset, size_t rd_size)
{
	size_t	i;
	size_t	start_index;

	i = 0;
	start_index = offset;
	while (start_index + i < rd_size)
	{
		++offset;
		++i;
		if (rd_buf[start_index + i - 1] == '\n')
			break;
	}
	*out = malloc(offset - start_index + 1);
	i = 0;
	while (start_index + i < offset)
	{
		(*out)[i] = rd_buf[start_index + i];
		i++;
	}
	return (offset);
}

char	*get_next_line(int fd)
{
	static size_t	offset = 0;
	static size_t	read_return;
	static char		read_buffer[BUFFER_SIZE];
	char			*out;
	size_t			outsize;			

	if (!offset)
		read_return = read(fd, read_buffer, BUFFER_SIZE);
	if (!read_return || read_return < 0)
		return (NULL);
	offset = write_to_output(read_buffer, &out, offset, read_return);
	if (offset == read_return && read_return == BUFFER_SIZE)
	{
		//RESIZE OUT AND KEEP READING
	}
	else if (offset == read_return || read_buffer[offset - 1] == '\n')
		return (out);
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*test;

	fd = open("test.txt", O_RDONLY);
	char	*b = malloc(BUFFER_SIZE);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}

// TODO : RESIZE LINE BUFFER
// TODO : RETURN LINE FROM LINE BUFFER
// TODO : CHECK FOR EOF (READ_RETURN)
// TODO : COPY FROM READ TO LINE BUFFER