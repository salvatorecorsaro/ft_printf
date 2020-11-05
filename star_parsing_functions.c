# include "ft_printf.h"

t_flags get_width_star(t_flags *flags, int value) {
    (*flags).width = (value >= 0) ? value : -value;
    (*flags).filler = (value >= 0) ? (*flags).filler : ' ';
    (*flags).minus = (value >= 0) ? (*flags).minus : 1;
    return (*flags);
}

t_flags get_precision_star(t_flags *flags, int value) {
    if (value >= 0)
        (*flags).precision = value;
    else
        (*flags).point = 0;
    return (*flags);
}

t_flags			treat_star(va_list args, t_flags flags, int *j)
{
    int			value;

    (*j)++;
    value = va_arg(args, int);
    if (flags.point == 0)
    {
        flags = get_width_star(&flags, value);
    }
    if (flags.point == 1)
    {
        flags = get_precision_star(&flags, value);
    }
    return (flags);
}




