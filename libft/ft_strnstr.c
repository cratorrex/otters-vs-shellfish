/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:01:02 by thtay             #+#    #+#             */
/*   Updated: 2025/11/20 18:01:04 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// I'm trying to find "d" in this string up to 12 characters. {NULL}
// But if I try to find nothing... {return big}
//

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (*little == '\0')
		return ((char *)big);
	if (!big)
		return (NULL);
	while (*big && len > i)
	{
		while (big[i + n] == little[n] && len > (i + n))
		{
			n++;
			if (little[n] == '\0')
				return ((char *)&big[i]);
		}
		n = 0;
		i++;
	}
	return (NULL);
}
