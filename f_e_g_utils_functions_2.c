//
// Created by Salvatore Corsaro on 2020-07-28.
//

#include "ft_printf.h"

char            *insert_zeroes(char *nbr, int precision)
{
    char	str[precision + 3];
    char	*tmp_buffer;
    size_t	strlen;
    int		i;

    strlen = ft_strlen(nbr);
    if (precision == 0)
        ft_strlcpy(str, nbr, 2);
    else
    {
        ft_strlcpy(str, nbr, strlen + 1);
        i = strlen;
        while (i <= precision + 1)
            str[i++] = '0';
        str[i] = '\0';
    }
    tmp_buffer = ft_strdup(str);
    return (tmp_buffer);
}

t_flags         get_zeroes_to_insert(t_flags flags, int *j)
{
    *j = 1;
    while (flags.d[++(*j)] != '\0')
    {
        if ((find_char_in_str("123456789", flags.d[*j])) == 1)
            break ;
    }
    free(flags.d);
    flags.d = round_nmb(flags.f, (*j - 1) + flags.precision, 5);
    *j = 1;
    while (flags.d[++(*j)] != '\0')
    {
        if (flags.d[*j] == '0')
        {
            flags.d[*j] = '.';
            flags.d[(*j) - 1] = '0';
        }
        else if ((flags.d[*j - 1] = flags.d[*j]))
        {
            flags.d[*j] = '.';
            break ;
        }
    }
    flags.e_nbr = -((*j) - 1);
    flags.tmp = ft_substr(flags.d, (*j) - 1, ft_strlen(flags.d) - ((*j) - 1));
    return (flags);
}

t_flags         prepare_e_string(t_flags fl, int *j)
{
    ft_strlcpy(fl.e, "e-", 3);
    fl.size = 1;
    fl.d = round_nmb(fl.f, fl.size, 5);
    *j = 1;
    while (fl.d[++(*j)] != '\0' && *j <= 18)
    {
        if ((fl.size++) && (find_char_in_str("123456789", fl.d[*j])) == 1)
            break ;
        free(fl.d);
        fl.d = round_nmb(fl.f, fl.size, 5);
    }
    if (*j > 18 && (fl.e[1] = '+'))
    {
        free(fl.d);
        fl.d = insert_zeroes("0.", fl.precision);
        return (fl);
    }
    fl = get_zeroes_to_insert(fl, j);
    free(fl.d);
    if (ft_strlen(fl.tmp) >= fl.str_length)
        fl.d = ft_substr(fl.tmp, 0, fl.str_length);
    else
        fl.d = insert_zeroes(fl.tmp, fl.precision);
    free(fl.tmp);
    return (fl);
}

t_flags         get_exponent_e(t_flags fl, unsigned long long int i_part, int *j)
{
    ft_strlcpy(fl.e, "e+", 3);
    while (i_part /= 10)
        fl.e_nbr++;
    fl.d = round_nmb((fl.f / ft_exponent_finder(10, fl.e_nbr)), fl.precision, 5);
    *j = ft_strlen(fl.d);
    while (--(*j) >= 0)
    {
        if (fl.d[*j] == '.' && *j >= 2)
        {
            fl.d[*j] = fl.d[(*j) - 1];
            fl.d[(*j) - 1] = '.';
        }
    }
    if (ft_strlen(fl.d) > fl.str_length)
    {
        fl.tmp = ft_substr(fl.d, 0, fl.str_length);
        fl.e_nbr += ft_strlen(fl.d) - fl.str_length;
        free(fl.d);
        fl.d = fl.tmp;
    }
    return (fl);
}

int             remove_zeroes(int precision, char *str)
{
    int		i;

    i = ft_strlen(str);
    while (--i >= 0)
    {
        if (!(str[i] == '0' || str[i] == '.'))
            break ;
        if (str[i] == '.')
        {
            str[i] = '\0';
            break ;
        }
        if (str[i] == '0')
        {
            precision--;
            str[i] = '\0';
        }
    }
    return (precision);
}
