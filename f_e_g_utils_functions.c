//
// Created by scorsaro on 23/7/20.
//

# include "ft_printf.h"


t_f_to_buffer          decimal_to_buffer(t_f_to_buffer var)
{
    int			i;

    var.zero_string[0] = '.';
    i = 1;
    if (var.dec_int_size < var.dec_len + 1)
    {
        while (var.dec_int_size++ < var.dec_len + 1)
            var.zero_string[i++] = '0';
    }
    var.zero_string[i] = '\0';
    var.tmp = i_to_buffer(var.dec_int, DIGITS);
    var.d = ft_strjoin(var.zero_string, var.tmp);
    var.d = check_precision(var.d, var.dec_len);
    free(var.tmp);
    return (var);
}

t_f_to_buffer          decimal_to_normal_nmb(t_f_to_buffer var)
{
    var.int_part = var.n;
    var.dec_part = var.n - var.int_part;
    var.dec_int = var.dec_part * ft_exponent_finder(10, var.dec_len);
    var.dec_int_size = 1;
    while ((var.dec_int) /= 10)
        (var.dec_int_size)++;
    var.dec_int = var.dec_part * ft_exponent_finder(10, var.dec_len + 1);
    var = check_rounding(var);
    var.dec_int /= 10;
    if (var.dec_int == 0)
        var.dec_int_size = 2;
    return (var);
}

char			*round_nmb(long double n, short int dec_len, short int rnd)
{
    t_f_to_buffer	var;

    var.n = (n >= 0) ? n : -n;
    var.dec_len = dec_len;
    var.rnd = rnd;
    var = decimal_to_normal_nmb(var);
    if (var.dec_len > 0)
        var = decimal_to_buffer(var);
    else
        var.d = ft_strdup("");
    var.tmp = i_to_buffer(var.int_part, DIGITS);
    var.buffer = ft_strjoin(var.tmp, var.d);
    free(var.tmp);
    free(var.d);
    return (var.buffer);
}

char		    *check_precision(char *dec_str, short int dec_len)
{
    size_t	strlen;
    int		diff;
    char	*tmp;

    strlen = ft_strlen(dec_str);
    diff = strlen - 1 - (size_t)dec_len;
    if (dec_len > 0 && diff > 0)
    {
        tmp = ft_substr(dec_str, diff + 1, dec_len + 1);
        free(dec_str);
        dec_str = ft_strjoin(".", tmp);
        free(tmp);
    }
    return (dec_str);
}

t_f_to_buffer	check_rounding(t_f_to_buffer var)
{
    unsigned long long int	aux;
    int						size;

    if ((var.dec_int % 10) >= (unsigned)var.rnd)
        var.dec_int += 10;
    aux = var.dec_int;
    size = 1;
    while (aux /= 10)
        size++;
    aux = var.dec_part * 10;
    if ((var.dec_len == 0 && aux >= (unsigned)var.rnd) ||
        (size > var.dec_int_size + 1 && aux + 1 >= (unsigned)var.rnd))
    {
        var.dec_int = 0;
        var.int_part++;
    }
    return (var);
}





