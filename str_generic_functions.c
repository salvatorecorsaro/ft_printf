//
// Created by Salvatore Corsaro on 2020-07-28.
//

#include "ft_printf.h"

int find_char_in_str(char *str, char c) {
    int i;

    i = 0;
    while (str[i] != '\0')
        if (str[i++] == c)
            return TRUE;
    return FALSE;
}

size_t ft_strlen(const char *str) {
    size_t len;

    if (!str)
        return 0;
    len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    char	*new_str;
    int		i;
    int		j;

    if (!s1 || !s2 ||
        !(new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return (0);
    i = 0;
    while (s1[i] != '\0')
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
    {
        new_str[i] = s2[j];
        i++;
        j++;
    }
    new_str[i] = '\0';
    return (new_str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t srcsize;
    size_t i;

    if (!dst || !src)
        return (0);
    srcsize = ft_strlen(src);
    i = 0;
    if (dstsize != 0)
    {
        while (src[i] != '\0' && i < (dstsize - 1))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (srcsize);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t c;
    size_t d;

    if (dstsize <= ft_strlen(dst))
        return (dstsize + ft_strlen(src));
    c = ft_strlen(dst);
    d = 0;
    while (src[d] != '\0' && c + 1 < dstsize)
    {
        dst[c] = src[d];
        c++;
        d++;
    }
    dst[c] = '\0';
    return (ft_strlen(dst) + ft_strlen(&src[d]));
}


