/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:16:15 by thtay             #+#    #+#             */
/*   Updated: 2025/11/19 16:16:17 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// z
//

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	total;

	total = 0;
	while (*src && (size - 1) > total && size > 0)
	{
		*dst = *src;
		dst++;
		src++;
		total++;
	}
	if (size > 0)
		*dst = '\0';
	while (*src)
	{
		total++;
		src++;
	}
	return (total);
}
