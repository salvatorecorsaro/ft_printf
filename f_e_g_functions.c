//
// Created by Salvatore Corsaro on 2020-07-28.
//

#include "ft_printf.h"


t_flags         print_conversion_f(t_flags flags, double n)
{
    flags.f = (n >= 0) ? n : -n;
    flags.big_u_int = flags.f;
    flags.buffer = round_nmb(flags.f, flags.precision, 5);
    if (flags.hash == 1 && flags.point == 1 && flags.precision == 0)
    {
        flags.tmp = ft_strjoin(flags.buffer, ".");
        free(flags.buffer);
        flags.buffer = flags.tmp;
    }
    return (flags);
}

t_flags			print_conversion_e(t_flags flags, double n)
{
    int		j;

    flags.f = (n >= 0) ? n : -n;
    flags.big_u_int = flags.f;
    flags.e_nbr = 0;
    flags.str_length = (flags.precision > 0) ? (size_t)flags.precision + 2 : 1;
    if (flags.big_u_int > 0)
        flags = get_exponent_e(flags, flags.big_u_int, &j);
    else
        flags = prepare_e_string(flags, &j);
    flags.tmp = i_to_buffer(((flags.e_nbr > 0) ? flags.e_nbr : -flags.e_nbr), DIGITS);
    if ((ft_strlen(flags.tmp)) == 1 && (ft_strlcat(flags.e, "0", 4)))
        ft_strlcat(flags.e, flags.tmp, 5);
    else
        ft_strlcat(flags.e, flags.tmp, 5);
    free(flags.tmp);
    if (flags.hash == 1 && flags.point == 1 && flags.precision == 0)
    {
        flags.tmp = ft_strjoin(flags.d, ".");
        free(flags.d);
        flags.d = flags.tmp;
    }
    flags.buffer = ft_strjoin(flags.d, flags.e);
    return (flags);
}

t_flags			print_conversion_g(t_flags fl, double n, int p)
{
    fl = print_conversion_e(fl, n);
    free(fl.buffer);
    free(fl.d);
    if (p > fl.e_nbr && fl.e_nbr >= -4)
    {
        fl.specif = 'f';
        fl.precision = p - (fl.e_nbr + 1);
        fl = print_conversion_f(fl, n);
        if (fl.hash == 0 && find_char_in_str(fl.buffer, '.') == 1)
            fl.precision = remove_zeroes(fl.precision, fl.buffer);
    }
    else
    {
        fl.specif = 'e';
        fl.precision = p - 1;
        fl = print_conversion_e(fl, n);
        if (fl.hash == 0 && find_char_in_str(fl.d, '.') == 1)
            fl.precision = remove_zeroes(fl.precision, fl.d);
        free(fl.buffer);
        fl.buffer = ft_strjoin(fl.d, fl.e);
    }
    return (fl);
}

void            print_conversion_f_e_g(int *prin_cnt, t_flags flags, double n)
{
    union u_double dbl;

    dbl.f = n;
    flags.sign = (dbl.bits.sign > 0) ? '-' : '+';
    flags.print_nmb_0 = 1;
    if (flags.point == 0)
        flags.precision = 6;
    if (flags.specif == 'f')
        flags = print_conversion_f(flags, n);
    if (flags.specif == 'e')
        flags = print_conversion_e(flags , n);
    if (flags.specif == 'g')
    {
        if (flags.point == 1 && flags.precision == 0)
            flags = print_conversion_g(flags, n, 1);
        else
            flags = print_conversion_g(flags, n , flags.precision);
    }
    print_flags(prin_cnt, flags);
    if (flags.specif == 'e')
        free(flags.d);
    free(flags.buffer);
}