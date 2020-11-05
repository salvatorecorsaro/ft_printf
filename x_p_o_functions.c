/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_p_o_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:50:25 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/16 17:50:29 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"



void print_conversion_x(int *printd_counter, t_flags flags, va_list args)
{
    u_length_switcher(&flags, args);
    flags.sign = 'u';
    flags.print_nmb_0 = FALSE;
    if (flags.big_u_int == 0)
        flags.hash = FALSE;
    if (flags.specif == 'x')
        flags.buffer = i_to_buffer(flags.big_u_int, HEXA_LOWER);
    else if (flags.specif == 'X')
        flags.buffer = i_to_buffer(flags.big_u_int, HEXA_UPPER);
    print_flags(printd_counter, flags);
    free(flags.buffer);
}

void	print_conversion_p(int *prin_cnt, t_flags fl, unsigned long int p)
{
    fl.sign = 'u';
    fl.print_nmb_0 = FALSE;
    fl.buffer = i_to_buffer(p, HEXA_LOWER);
    print_flags(prin_cnt, fl);
    free(fl.buffer);
}

void print_conversion_o(int *prin_cnt, t_flags flags, va_list args)
{
    u_length_switcher(&flags, args);
    flags.sign = 'u';
    flags.print_nmb_0 = TRUE;
    if (flags.point == TRUE && flags.precision == 0 && flags.hash == FALSE)
        flags.print_nmb_0 = FALSE;
    if (flags.big_u_int == 0)
        flags.hash = FALSE;
    flags.buffer = i_to_buffer(flags.big_u_int, OCTAL);
    print_flags(prin_cnt, flags);
    free(flags.buffer);
}
