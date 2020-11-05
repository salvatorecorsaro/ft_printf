/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_flags_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:50:12 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/16 17:50:15 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void            print_width(int *printed_counter, t_flags flags) {
    if (flags.sign == '-' || (flags.plus == TRUE && flags.sign == '+') ||
        (flags.space == TRUE && flags.plus == FALSE && flags.sign == '+'))
        flags.width--;
    if (flags.precision <= (int) flags.str_length)
        flags.precision = (int) flags.str_length;
    if (flags.filler == '0' && (flags.minus == TRUE || flags.point == TRUE) &&
        !(flags.specif == 'f' && flags.minus == FALSE))
        flags.filler = ' ';
    while (flags.width > flags.precision) {
        ft_putchar_with_counter(flags.filler, printed_counter);
        flags.width--;
    }
}

void            print_zeros(int *printed_counter, t_flags flags) {
    int		j;

    if ((flags.specif == 'x' && flags.hash == TRUE) || flags.specif == 'p')
        ft_putstr_with_counter("0x", printed_counter, 2);
    if (flags.specif == 'X' && flags.hash == TRUE)
        ft_putstr_with_counter("0X", printed_counter, 2);
    if (flags.specif == 'o' && flags.hash == TRUE)
        ft_putchar_with_counter('0', printed_counter);
    if (flags.minus == FALSE && flags.filler == '0')
        print_width(printed_counter, flags);
    if (flags.point == TRUE)
    {
        j = flags.precision;
        while (j-- > (int)flags.str_length)
            ft_putchar_with_counter('0', printed_counter);
    }
}

void            print_flags(int *printed_counter, t_flags flags) {
    flags.str_length = ft_strlen(flags.buffer);
    if (flags.big_u_int == 0 && flags.point == TRUE && flags.precision == FALSE
        && flags.print_nmb_0 == FALSE)
        flags.width++;
    if (((flags.specif == 'x' || flags.specif == 'X') && flags.hash == TRUE) ||
        flags.specif == 'p')
        flags.width -= 2;
    if (flags.specif == 'o' && flags.hash == TRUE)
        flags.width -= 1;
    if (flags.specif == 'o' && flags.hash == TRUE && flags.point == TRUE)
        flags.precision -= 1;
    if (flags.point == TRUE && flags.specif != 'f')
        flags.filler = ' ';
    if (flags.minus == FALSE && flags.filler == ' ')
        print_width(printed_counter, flags);
    if (flags.sign == '-' || (flags.plus == TRUE && flags.sign == '+'))
        ft_putchar_with_counter(flags.sign, printed_counter);
    if (flags.space == TRUE && flags.plus == FALSE && flags.sign == '+')
        ft_putchar_with_counter(' ', printed_counter);
    print_zeros(printed_counter, flags);
    if (!(flags.big_u_int == 0 && flags.point == TRUE && flags.precision == FALSE) ||
        flags.print_nmb_0 == TRUE)
        ft_putstr_with_counter(flags.buffer, printed_counter, ft_strlen(flags.buffer));
    if (flags.minus == TRUE)
        print_width(printed_counter, flags);
}
