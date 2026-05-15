/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:23:19 by thtay             #+#    #+#             */
/*   Updated: 2025/11/22 18:23:22 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// \f \n \r \t \v ' '
// 12 10 13 09 11 32
//
// no need to check for errors but
// 2147483647 anyways
//

#include "libft.h"

static int	parse_num(char *ptr, int sign)
{
	int	num;

	num = 0;
	while (*ptr >= '0' && *ptr <= '9')
	{
		num = num * 10 + (int)(*ptr - '0');
		ptr++;
	}
	return (num * sign);
}

int	ft_atoi(const char *nptr)
{
	char	*ptr;
	int		sign;

	ptr = (char *)nptr;
	sign = 1;
	while ((*ptr >= 9 && *ptr <= 13) || *ptr == 32)
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	return (parse_num(ptr, sign));
}
