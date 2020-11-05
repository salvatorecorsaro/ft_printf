/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percentage_c_s_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:49:47 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/29 19:35:22 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_filler(int *len, t_flags flags)
{
	while (flags.width > flags.precision) {
		ft_putchar_with_counter(flags.filler, len);
		flags.width--;
	}
}

void	print_conversion_percentage(int *printed_counter, t_flags flags)
{
	flags.precision = 1;
	if (flags.minus == FALSE)
		print_filler(printed_counter, flags);
	ft_putchar_with_counter('%', printed_counter);
	if (flags.minus == TRUE){
		flags.filler = ' ';
	print_filler(printed_counter, flags);
	}
}

void	print_conversion_c(int *printed_counter, t_flags flags, char c)
{
	flags.filler = ' ';
	flags.precision = 1;
	if (flags.minus == FALSE)
		print_filler(printed_counter, flags);
	ft_putchar_with_counter(c, printed_counter);
	if (flags.minus == TRUE)
		print_filler(printed_counter, flags);
}

void	print_conversion_s(int *printed_counter, t_flags flags, char *str)
{
	flags.filler = ' ';
	if (str == NULL)
		str = "(null)";
	if ((flags.point == TRUE && flags.precision > (int) ft_strlen(str))
	|| flags.point == FALSE)
		flags.precision = ft_strlen(str);
	if (flags.minus == FALSE)
		print_filler(printed_counter, flags);
	ft_putstr_with_counter(str, printed_counter, flags.precision);
	if (flags.minus == TRUE)
		print_filler(printed_counter, flags);
}
