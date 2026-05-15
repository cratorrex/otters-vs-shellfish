/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:02:50 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:02:53 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// malloc (s1 cat s2)
//
// ERROR NULL

#include "libft.h"

static size_t	len(char const *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		i ++;
		s ++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	size_t	incr;
	char	*ret;

	ret = malloc(len(s1) + len(s2) + 1);
	if (!ret)
		return (NULL);
	total = 0;
	incr = 0;
	while (s1 && s1[total])
	{
		ret[total] = s1[total];
		total++;
	}
	while (s2 && s2[incr])
	{
		ret[total + incr] = s2[incr];
		incr++;
	}
	ret[total + incr] = '\0';
	return (ret);
}
