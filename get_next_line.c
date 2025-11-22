#include "get_next_line.h"
#include <stdio.h>

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t			counter;
	unsigned char	*ptr;

	ptr = (unsigned char *)pointer;
	counter = 0;
	while (counter < count)
	{
		*(ptr + counter) = (unsigned char)value;
		counter++;
	}
	return (pointer);
}

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (!dst && !src)
		return (NULL);
	while (counter < size)
	{
		*(unsigned char *)(dst + counter) = *(unsigned char *)(src + counter);
		counter++;
	}
	return (dst);
}

char	*ft_strdup(const char *str)
{
	size_t	strlen;
	char	*result;

	strlen = 0;
    while (str[strlen])
    {
        strlen++;
    }
	result = malloc(strlen + 1);
	if (!result)
		return (NULL);
	strlen = 0;
    while (str[strlen])
    {
        result[strlen] = str[strlen];
        strlen++;
    }
    result[strlen] = 0;
	return (result);
}

t_line    *init_line_buf(void)
{
    t_line  *out;

    out = malloc(sizeof(t_line));
    if (!out)
        return (NULL);
    out->content = malloc(BUFFER_SIZE + 1);
    if (!out->content)
    {
        free(out);
        return (NULL);
    }
    ft_memset(out->content, 0, BUFFER_SIZE + 1);
    out->capacity = BUFFER_SIZE;
    out->size = 0;
    return (out);
}

char    *append(t_line *l, t_rd rd, int s)
{
    char    *tmp;

    if (l->size + s >= l->capacity)
    {
        tmp = malloc(l->capacity);
        if (!tmp)
            return (NULL);
        tmp = ft_memcpy(tmp, l->content, l->capacity);
        free(l->content);
        l->content = malloc(l->capacity * 2 + 1);
        if (!l->content)
            return (NULL);
        ft_memcpy(l->content, tmp, l->capacity);
        l->capacity *= 2;
        free(tmp);
    }
    ft_memcpy(l->content + l->size, rd.buf + rd.start, s);
    l->size += s;
    l->content[l->size] = 0;
    return (l->content);
}

char    *cpy_until_nl(t_line *l, t_rd *rd)
{
    while (rd->end < (size_t)rd->o)
    {
        if (rd->buf[rd->end] == '\n')
        {
            rd->end++;
            break;
        }
        rd->end++;
    }
    l->content = append(l, *rd, rd->end - rd->start);
    if (rd->end >= (size_t) rd->o)
    {
        rd->end = 0;
        rd->o = 0;
        ft_memset(rd->buf, 0, BUFFER_SIZE);
    }
    rd->start = rd->end;
    return (l->content);
}

char    *get_next_line(int fd)
{
    static t_rd         rd = {"", 0, 0, 0};
    t_line              *l;
    char                *out;

    out = NULL;
    l = init_line_buf();
    if (!l)
        return (NULL);
    while (rd.end)
    {
        l->content = cpy_until_nl(l, &rd);
        if (l->content[l->size - 1] == '\n')
            break;
    }
    while (!rd.end)
    {
        rd.o = read(fd, rd.buf, BUFFER_SIZE);
        if (rd.o <= 0)
            break;
        l->content = cpy_until_nl(l, &rd);
        if (l->content[l->size - 1] == '\n')
            break;
    }
    if (l->size && rd.o >= 0)
        out = ft_strdup(l->content);
    free(l->content);
    free(l);
    return (out);
}

/* int main()
{
    int fd = open("tests/big_line_with_nl", O_RDONLY, 0666);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
} */