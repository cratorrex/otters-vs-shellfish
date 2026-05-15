/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:57:38 by thtay             #+#    #+#             */
/*   Updated: 2025/11/21 17:57:40 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// [      ] SRC
//      [      ] DEST (in this case, go backwards)
//
// SRC >> Temp [      ] >> DEST (???) (NO)
//
// Normal behaviour is MEMCPY, otherwise INVERT IT.
//

#include "libft.h"

static void	*ft_memmove_decr(void *dest, const void *src, size_t n)
{
	unsigned char	*ret;
	unsigned char	*cast;

	ret = (unsigned char *)dest;
	cast = (unsigned char *)src;
	while (n > 0)
	{
		n--;
		ret[n] = cast[n];
	}
	return ((void *)ret);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ret;
	unsigned char	*cast;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		return (ft_memmove_decr(dest, src, n));
	}
	i = 0;
	ret = (unsigned char *)dest;
	cast = (unsigned char *)src;
	while (n > i)
	{
		ret[i] = cast[i];
		i++;
	}
	return ((void *)ret);
}
