/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:51:20 by thtay             #+#    #+#             */
/*   Updated: 2025/12/30 15:51:21 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//0123456789 {:;<=>?} << 58 - 63 >> = 65 - 70 (X) / 97 - 102 (x)
//simply -32*mode + num + 97 - 10
static void	write_hex(char *hex, int mode)
{
	while (*hex)
	{
		if (*hex >= '0' && *hex <= '9')
			ft_putchar_fd(*hex, 1);
		if (*hex >= 58 && *hex <= 63)
		{
			ft_putchar_fd((39 - (32 * mode) + (*hex)), 1);
		}
		hex++;
	}
}

static char	*handle_base16(unsigned int itoa, int size)
{
	char	*ret;

	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	size--;
	if (itoa == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	while (itoa > 0)
	{
		ret[size] = (itoa % 16) + '0';
		itoa = itoa / 16;
		size--;
	}
	return (ret);
}

static int	length(unsigned int hexa)
{
	int	size;

	size = 1;
	while (hexa / 16 > 0)
	{
		size ++;
		hexa /= 16;
	}
	return (size);
}

//0 for lower (x), 1 for upper (X)
int	handle_hex(unsigned int hexa, int mode)
{
	int		size;
	char	*htp;

	size = length(hexa);
	htp = handle_base16(hexa, size);
	write_hex(htp, mode);
	free(htp);
	return (size);
}
