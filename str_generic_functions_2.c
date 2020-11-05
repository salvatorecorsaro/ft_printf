//
// Created by Salvatore Corsaro on 2020-07-28.
//

# include "ft_printf.h"

char            *ft_strdup(const char *s1)
{
    char	*s2;
    size_t	size;
    size_t	i;

    size = ft_strlen(s1) + 1;
    if (!(s2 = (char *)malloc(size)))
        return (0);
    i = 0;
    while (i < size)
    {
        ((unsigned char *)s2)[i] = ((unsigned char *)s1)[i];
        i++;
    }
    return (s2);
}

char            *ft_substr(char const *s, unsigned int start, size_t len)
{
    char	*new_str;
    size_t	i;
    size_t	j;

    if (!s || !(new_str = (char *)malloc(len + 1)))
        return (0);
    i = start;
    j = 0;
    while (i < ft_strlen(s) && j < len)
        new_str[j++] = s[i++];
    new_str[j] = '\0';
    return (new_str);
}

void            ft_putchar_with_counter(char c, int *printd_counter)
{
    write(1, &c, 1);
    (*printd_counter)++;
}

void            ft_putstr_with_counter(char *str, int *printd_counter, int size)
{
    int i;

    if (str != NULL) {
        i = 0;
        while (str[i] && i < size)
            ft_putchar_with_counter(str[i++], printd_counter);
    }
}