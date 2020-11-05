/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:55:35 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/29 19:08:20 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			conversion_switch(va_list args, int *prin_count, t_flags flags)
{
	int					*p;

	if (flags.specif == 'c')
		print_conversion_c(prin_count, flags, va_arg(args, int));
	if (flags.specif == 's')
		print_conversion_s(prin_count, flags, va_arg(args, char *));
	if (flags.specif == 'i' || flags.specif == 'd' || flags.specif == 'u')
        print_conv_i_d_u(prin_count, flags, args);
	if (flags.specif == 'x' || flags.specif == 'X')
		print_conversion_x(prin_count, flags, args);
	if (flags.specif == 'o')
		print_conversion_o(prin_count, flags, args);
	if (flags.specif == 'p')
		print_conversion_p(prin_count, flags, va_arg(args, unsigned long int));
	if (flags.specif == 'f' || flags.specif == 'e' || flags.specif == 'g')
		print_conversion_f_e_g(prin_count, flags, va_arg(args, double));
	if (flags.specif == 'n' && (p = va_arg(args, int *)))
		*p = *prin_count;
	if (flags.specif == '%')
		print_conversion_percentage(prin_count, flags);
}

t_flags			get_flags(const char *frmt, int *i, t_flags *flags)
{
	(*flags).specif = frmt[(*i)++];
	(*flags).minus = find_char_in_str((*flags).all_formats_founded, '-');
	(*flags).plus = find_char_in_str((*flags).all_formats_founded, '+');
	(*flags).space = find_char_in_str((*flags).all_formats_founded, ' ');
	(*flags).hash = find_char_in_str((*flags).all_formats_founded, '#');
	(*flags).width = 0;
	(*flags).point = FALSE;
	(*flags).precision = 0;
	(*flags).length = 0;
	(*flags).filler = ' ';
	return (*flags);
}

void			analyze_formats(va_list args, const char *frmt, int *l, int *i)
{
	t_flags				flags;
	int					j;

	j = 0;
	while (find_char_in_str(ALL_FLAGS, frmt[*i]) && j < 19)
		flags.all_formats_founded[j++] = frmt[(*i)++];
	flags.all_formats_founded[j] = '\0';
	if (find_char_in_str(CONVERSION, frmt[*i]))
	{
		flags = get_flags(frmt, i, &flags);
		flags = analyze_more_formats(args, flags);
		conversion_switch(args, l, flags);
	}
	else
		(*l) = -1;
}

t_flags			analyze_more_formats(va_list args, t_flags flags)
{
	int					j;

	j = 0;
	parse_zero_flags(&flags, &j);
	if (flags.all_formats_founded[j] == '*')
		flags = treat_star(args, flags, &j);
	parse_width(&flags, &j);
	if (flags.all_formats_founded[j] == '.')
	{
		flags.point = 1;
		if (flags.all_formats_founded[++j] == '*')
			flags = treat_star(args, flags, &j);
		parse_precision_value(&flags, &j);
	}
	parse_length_l(&flags, &j);
	parse_length_h(&flags, j);
	return (flags);
}

int				ft_printf(const char *format, ...)
{
	va_list				args;
	int					printed_counter;
	int					i;

	va_start(args, format);
	printed_counter = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			ft_putchar_with_counter(format[i++], &printed_counter);
		else
		{
			i++;
			analyze_formats(args, format, &printed_counter, &i);
			if (printed_counter == -1)
				return (-1);
		}
	}
	va_end(args);
	return (printed_counter);
}
