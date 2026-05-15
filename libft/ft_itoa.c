/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:03:44 by thtay             #+#    #+#             */
/*   Updated: 2025/11/25 17:49:17 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// int to ascii
//
// ERROR NULL

#include "libft.h"
#include <limits.h>
#include <stdio.h>

//strlen then pass into helper
static char	*convert(size_t len, int sign, long n)
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
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}

static size_t	length(long n)
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

char	*ft_itoa(int n)
{
	size_t	len;
	long	m;
	int		sign;

	len = 1;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		m = n;
		m = -m;
		len++;
		len = len + length(m);
		return (convert(len, sign, ((long)n) * sign));
	}
	len = len + length((long)n);
	return (convert(len, sign, (long)n));
}
