#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE    50
#endif

void    ft_memset(void *ptr, int value, size_t n)
{
    size_t c;

    c = 0;
    while (c < n)
    {
        *(unsigned char *) (ptr + c) = (unsigned char) value;
        c++;
    }
}

void    *resize(void *ptr, size_t oldsize)
{
    void    *new_ptr;
    size_t  c;
    
    new_ptr = malloc((oldsize * 2) + 1);
    c = 0;
    while (c < oldsize)
    {
        *(unsigned char *) (new_ptr + c) = *(unsigned char *) (ptr + c);
        c++;
    }
    while (c < oldsize * 2)
    {
        *(unsigned char *) (new_ptr + c) = 0;
        c++;
    }
    return (new_ptr);
}

#include <stdio.h>
int main()
{
    size_t size = 2;
    unsigned char       *buf = malloc(size);
    for (int i = 0; i < 10; i++)
    {
        ft_memset(buf, 'A', size);
        resize(buf, size);
        for (size_t i = 0; i < size; i++)
        {
            printf("%c", buf[i]);
        }
        printf("\n");
        size *= 2;
    }
    
}



