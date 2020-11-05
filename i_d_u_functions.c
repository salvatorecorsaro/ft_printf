/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_d_u_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 19:14:16 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/29 19:22:21 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_conv_i_d_u(int *prin_cnt, t_flags flags, va_list args)
{
	if (flags.specif == 'i' || flags.specif == 'd')
	{
		length_switcher(&flags, args);
		flags.sign = (flags.big_int >= 0) ? '+' : '-';
		flags.big_u_int = (flags.big_int >= 0) ? flags.big_int : -flags.big_int;
	}
	if (flags.specif == 'u')
	{
		u_length_switcher(&flags, args);
		flags.sign = 'u';
	}
	flags.print_nmb_0 = FALSE;
	flags.buffer = i_to_buffer(flags.big_u_int, DIGITS);
	print_flags(prin_cnt, flags);
	free(flags.buffer);
}

char		*i_to_buffer(unsigned long long int nbr, char *base)
{
	char					*tmp_buffer;
	unsigned long long int	tmp_nbr;
	size_t					size;
	int						base_len;

	base_len = ft_strlen(base);
	tmp_nbr = nbr;
	size = 1;
	while (nbr /= base_len)
		size++;
	if (!(tmp_buffer = (char *)malloc(size + 1)))
		return (0);
	tmp_buffer[size--] = '\0';
	while (tmp_nbr > 0)
	{
		tmp_buffer[size--] = base[tmp_nbr % base_len];
		tmp_nbr /= base_len;
	}
	if (size == 0 && tmp_buffer[1] == '\0')
		tmp_buffer[0] = '0';
	return (tmp_buffer);
}

long double	ft_exponent_finder(long double n, unsigned int pow)
{
	return (pow ? n * ft_exponent_finder(n, pow - 1) : 1);
}

void		u_length_switcher(t_flags *flags, va_list args)
{
	if ((*flags).length <= 0)
		(*flags).big_u_int = va_arg(args, unsigned int);
	else if ((*flags).length == 1)
		(*flags).big_u_int = va_arg(args, unsigned long int);
	else if ((*flags).length >= 2)
		(*flags).big_u_int = va_arg(args, unsigned long long int);
}

void		length_switcher(t_flags *flags, va_list args)
{
	if ((*flags).length <= 0)
		(*flags).big_int = va_arg(args, int);
	else if ((*flags).length == 1)
		(*flags).big_int = va_arg(args, long int);
	else if ((*flags).length >= 2)
		(*flags).big_int = va_arg(args, long long int);
}
