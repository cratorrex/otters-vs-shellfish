/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:15:28 by thtay             #+#    #+#             */
/*   Updated: 2025/11/19 16:15:30 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// v[3] you don't need to fafo atoi
// por favor
//

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	total;
	size_t	srclen;

	total = 0;
	srclen = ft_strlen(src);
	while (*dst && (size - 1) > total && size > 0)
	{
		dst++;
		total++;
	}
	if (*dst != '\0')
		return (size + srclen);
	while (*src)
	{
		if (size > total + 1)
		{
			*dst = *src;
			dst++;
		}
		src++;
		total++;
	}
	*dst = '\0';
	return (total);
}
