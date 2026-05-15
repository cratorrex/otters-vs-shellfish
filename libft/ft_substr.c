/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:02:21 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:02:23 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// return a malloc of substring s{   |>> len >>|  }
//                                   ^start
// len is maxim|{DON'T MALLOC AFTER NUL}  //
//
// ERROR NULL

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	n;
	char	*ret;

	i = 0;
	while (ft_strlen(s) > start && len > i && s[start + (int)i])
		i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	n = 0;
	while (i > n && s[start + (int)n])
	{
		ret[n] = s[start + (int)n];
		n++;
	}
	ret[n] = '\0';
	return (ret);
}
