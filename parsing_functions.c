/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 19:22:45 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/29 19:32:08 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_width(t_flags *flags, int *j)
{
	while ((*flags).all_formats_founded[(*j)] != '\0' &&
	find_char_in_str(DIGITS, (*flags).all_formats_founded[(*j)]))
	{
		(*flags).width = 10 * (*flags).width +
		(*flags).all_formats_founded[(*j)++] - '0';
	}
}

void	parse_precision_value(t_flags *flags, int *j)
{
	while ((*flags).all_formats_founded[(*j)] != '\0' &&
	find_char_in_str(DIGITS, (*flags).all_formats_founded[(*j)]))
	{
		(*flags).precision = 10 * (*flags).precision +
		(*flags).all_formats_founded[(*j)++] - '0';
	}
}

void	parse_zero_flags(t_flags *flags, int *j)
{
	while ((*flags).all_formats_founded[(*j)] != '\0' &&
	find_char_in_str(FLAGS, (*flags).all_formats_founded[(*j)]))
	{
		if ((*flags).all_formats_founded[(*j)++] == '0')
			(*flags).filler = '0';
	}
}

void	parse_length_l(t_flags *flags, int *j)
{
	while ((*flags).all_formats_founded[(*j)] != '\0' &&
	find_char_in_str("l", (*flags).all_formats_founded[(*j)++]))
	{
		(*flags).length++;
	}
}

void	parse_length_h(t_flags *flags, int j)
{
	while ((*flags).all_formats_founded[j] != '\0' &&
	find_char_in_str("h", (*flags).all_formats_founded[j++]))
	{
		(*flags).length--;
	}
}
