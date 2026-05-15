/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:51:39 by thtay             #+#    #+#             */
/*   Updated: 2025/12/30 15:51:40 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//reminder to add to libft
static char	*ft_utoa(size_t len, unsigned int n)
{
	char	*ret;

	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	len--;
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	while (n > 0)
	{
		ret[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (ret);
}

static size_t	length(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n / 10 > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	handle_uint(unsigned int num)
{
	char	*val;
	size_t	len;

	len = 1 + length(num);
	val = ft_utoa(len, num);
	ft_putstr_fd(val, 1);
	free(val);
	return (len);
}
