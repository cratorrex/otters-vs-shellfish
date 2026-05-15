/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:50:24 by thtay             #+#    #+#             */
/*   Updated: 2025/11/20 20:50:26 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// >>>>>>>>>|>>>>>
//

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ret;

	i = 0;
	ret = (unsigned char *)s;
	while (n > i)
	{
		if (ret[i] == (unsigned char)c)
			return ((void *)&ret[i]);
		i++;
	}
	return (NULL);
}
