/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:38:26 by thtay             #+#    #+#             */
/*   Updated: 2025/11/21 15:38:29 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//
//

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ret;
	unsigned char	*cast;

	i = 0;
	if (!dest && !src)
		return (NULL);
	ret = (unsigned char *)dest;
	cast = (unsigned char *)src;
	while (n > i)
	{
		ret[i] = cast[i];
		i++;
	}
	return ((void *)ret);
}
