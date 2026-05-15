/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:29 by thtay             #+#    #+#             */
/*   Updated: 2025/12/19 21:36:32 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////||
//                                            ||
//   malloc, free, write    <-- libft         ||
//   va_start, va_arg, va_copy, va_end        ||
//                                            |||||||||
//   c char       d decimal     x small hex          ||
//   s string     i integer     X UPPER HEX          ||
//   p pointer    u unsigned    % Control / escape   ||
//                                                   ||
/////////////////////////////////////////////////////||

#include "ft_printf.h"

static int	handle_end(const char *str, int incr)
{
	char	*val;
	int		sign;

	sign = 0;
	val = ft_strchr(str, '%');
	while (val[1] != 0 && *val == '%')
	{
		val++;
		sign += 1;
	}
	if (val[1] != 0 && sign <= 1)
	{
		ft_putchar_fd ('%', 1);
		return (incr + 1);
	}
	return (-1);
}

static int	print_pass(const char *str, va_list control)
{
	int		incr;
	int		prog;

	incr = 0;
	prog = 0;
	while (str[prog])
	{
		if (str[prog] == '%')
		{
			prog++;
			if (str[prog] == '\0')
				return (handle_end(str, incr));
			incr += pf_handle(str[prog], control);
			prog++;
			continue ;
		}
		ft_putchar_fd(str[prog], 1);
		prog++;
		incr++;
	}
	return (incr);
}

int	ft_printf(const char *str, ...)
{
	va_list	control;
	int		ret;

	va_start(control, str);
	if (!str)
		return (-1);
	ret = print_pass(str, control);
	va_end(control);
	return (ret);
}
