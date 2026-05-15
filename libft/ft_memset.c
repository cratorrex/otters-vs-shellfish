/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:18:32 by thtay             #+#    #+#             */
/*   Updated: 2025/11/20 21:18:35 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//
//

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ret;

	i = 0;
	ret = (unsigned char *)s;
	while (n > i)
	{
		ret[i] = c;
		i++;
	}
	return (s);
}
