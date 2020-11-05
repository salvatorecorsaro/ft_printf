/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorsaro <scorsaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:54:45 by scorsaro          #+#    #+#             */
/*   Updated: 2020/07/28 19:26:30 by scorsaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** LIBRARIES INCLUDED
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

/*
** MACROS USED IN THE PROJECT
*/

# define TRUE 1
# define FALSE 0
# define FLAGS "-+#0 "
# define ALL_FLAGS "-+#0 *.0123456789lh"
# define CONVERSION "cspdiuxX%onfge"
# define DIGITS "0123456789"
# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"
# define OCTAL "01234567"

/*
** STRUCTS USED IN THE PROJECT
*/

typedef struct				s_flags
{
	char					all_formats_founded[20];
	char					specif;
	char					filler;
	char					minus;
	char					plus;
	char					space;
	char					hash;
	int						width;
	char					point;
	int						precision;
	char					length;
	char					print_nmb_0;
	char					sign;
	unsigned long long int	big_u_int;
	long long int			big_int;
	char					*buffer;
	char					*d;
	char					*tmp;
	long double				f;
	char					e[5];
	int						e_nbr;
	int						size;
	size_t					str_length;
}							t_flags;

typedef struct	s_f_to_buffer
{
    long double				n;
    short int				dec_len;
    short int				rnd;
    unsigned long long int	int_part;
    long double				dec_part;
    unsigned long long int	dec_int;
    int						dec_int_size;
    char					*buffer;
    char					*d;
    char					*tmp;
    char					zero_string[20];
}				t_f_to_buffer;

typedef struct	s_double
{
    uint64_t	mantissa		:52;
    uint64_t	exponent	:11;
    uint64_t	sign		:1;

}				t_double;

union			u_double
{
    double	f;
    t_double	bits;
}				u_double_bit;


/*
 * LIST OF FUNCTIONS
 */


/*
 * str_generic_functions.c
 * A series of functions that works with strings
 */

int             find_char_in_str(char *str, char c);

size_t          ft_strlen(const char *str);

char            *ft_strjoin(char const *s1, char const *s2);

size_t          ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t          ft_strlcat(char *dst, const char *src, size_t dstsize);

/*
 * str_generic_functions_2.c
 * A series of functions that works with strings.
 */

char            *ft_strdup(const char *s1);

char            *ft_substr(char const *s, unsigned int start, size_t len);

void            ft_putchar_with_counter(char c, int *printd_counter);

void            ft_putstr_with_counter(char *str, int *printd_counter, int size);

/*
 * ft_printf.c
 * Main function used to analyze the format and store the flags and specifier.
 */

int             ft_printf(const char *str, ...);

void            analyze_formats(va_list args, const char *frmt, int *l, int *i);

t_flags         analyze_more_formats(va_list args, t_flags flags);

void            conversion_switch(va_list args, int *prin_count, t_flags flags);

/*
 * parsing_functions.c
 * Functions used to parse the format string.
 */

void parse_width(t_flags *flags, int *j);

void parse_precision_value(t_flags *flags, int *j);

void parse_zero_flags(t_flags *flags, int *j);

void parse_length_l(t_flags *flags, int *j);

void parse_length_h(t_flags *flags, int j);

/*
 * star_parsing_functions.c
 * Functions used to parse star from the args.
 */

t_flags         treat_star(va_list args, t_flags flags, int *j);

t_flags get_precision_star(t_flags *flags, int value);

t_flags get_width_star(t_flags *flags, int value);
/*
 * printing_flags_functions.c
 * Functions used to print the formatted result of the parsing.
 */
void            print_width(int *printed_counter, t_flags flags);

void            print_zeros(int *printed_counter, t_flags flags);

void            print_flags(int *printed_counter, t_flags flags);

/*
 * percentage_c_s_functions.c
 * Functions used to prepare for percentage, single character and strings printing.
 */

void            print_filler(int *len, t_flags flags);

void            print_conversion_percentage(int *printed_counter, t_flags flags);

void            print_conversion_c(int *printed_counter, t_flags flags, char c);

void            print_conversion_s(int *printed_counter, t_flags flags, char *str);

/*
 * i_d_u_functions.c
 * Functions used to prepare for i, d, u printing.
 */

void            print_conv_i_d_u(int *prin_cnt, t_flags flags, va_list args);

char            *i_to_buffer(unsigned long long int nbr, char *base);

long double     ft_exponent_finder(long double n, unsigned int pow);

void u_length_switcher(t_flags *flags, va_list args);

void length_switcher(t_flags *flags, va_list args);

/*
 * x_p_o_functions.c
 * Functions used to prepare for hexadecimal, pointers and octal conversion printing.
 */
void            print_conversion_x(int *printd_counter, t_flags flags, va_list args);

void            print_conversion_p(int *prin_cnt, t_flags flags, unsigned long int pointer_address);

void            print_conversion_o(int *prin_cnt, t_flags flags, va_list args);

void            print_conversion_f_e_g(int *prin_cnt, t_flags flags, double n);

t_flags			print_conversion_e(t_flags flags, double n);

/*
 * f_e_g_functions.c
 * Switcher with the main functions necessary for f, e, g conversions.
 */

void            print_conversion_f_e_g(int *prin_cnt, t_flags flags, double n);

t_flags         print_conversion_f(t_flags flags, double n);

t_flags			print_conversion_e(t_flags flags, double n);

t_flags			print_conversion_g(t_flags fl, double n, int p);

/*
 * f_e_g_utils_functions.c
 * A series of auxiliaries functions used for the f, e, g conversion.
 */

t_f_to_buffer          decimal_to_buffer(t_f_to_buffer var);

t_f_to_buffer          decimal_to_normal_nmb(t_f_to_buffer var);

char			*round_nmb(long double n, short int dec_len, short int rnd);

char            *check_precision(char *dec_str, short int dec_len);

t_f_to_buffer          check_rounding(t_f_to_buffer var);

/*
 * f_e_g_utils_functions_2.c
 * A series of auxiliaries functions used for the f, e, g conversion.
 */

char		    *insert_zeroes(char *nbr, int precision);

t_flags         get_zeroes_to_insert(t_flags flags, int *j);

t_flags         prepare_e_string(t_flags fl, int *j);

t_flags         get_exponent_e(t_flags fl, unsigned long long int i_part, int *j);

int             remove_zeroes(int precision, char *str);






#endif
