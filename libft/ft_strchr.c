/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:40:24 by thtay             #+#    #+#             */
/*   Updated: 2025/11/19 11:40:26 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// find the first occurrence of 'c' in 's' and return the *pointer
// stdio.h >> NULL
//

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ret;

	ret = (unsigned char *)s;
	while (*ret != (unsigned char) c && *ret != '\0')
	{
		ret++;
	}
	if (*ret == '\0' && (unsigned char) c != '\0')
		return (NULL);
	else
		return ((char *)ret);
}
