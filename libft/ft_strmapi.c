/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:04:21 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:04:22 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// foreach in *s { function *f(); }
// string iterate
//
// >> >> index, char at index
// >> *f(index, char[index])
//
// malloc size_of *s
// return *new
//

#include "libft.h"

// static char	incr(unsigned int i, char c)
// {
// 	if (c + i > 126)
// 		return (c);
// 	return (c + i);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	new = malloc (len + 1);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
