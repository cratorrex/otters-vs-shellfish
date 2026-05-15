/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:03:19 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:03:20 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// trim set from s1
// return ({set} text {set}) >> s1
// set text successtestset |>| " text succ"
//
// ERROR NULL

#include "libft.h"

// match = strnstr x substr, returning match start
static size_t	m_start(const char *big, const char *lil)
{
	size_t	i;
	size_t	n;

	i = 0;
	while (big[i])
	{
		n = 0;
		while (lil[n])
		{
			if (big[i] == lil[n] && lil[n] != '\0')
				break ;
			n++;
		}
		if (lil[n] == '\0')
		{
			if (i == 0)
				return (0);
			return (i);
		}
		i++;
	}
	return (i);
}

// match = strnstr x substr, returning match end
static size_t	m_end(const char *big, const char *lil)
{
	size_t	i;
	size_t	n;

	i = 0;
	while (big[i])
		i++;
	while (i > 0)
	{
		i--;
		n = 0;
		while (lil[n])
		{
			if (big[i] == lil[n] && lil[n] != '\0')
				break ;
			n++;
		}
		if (lil[n] == '\0')
			return (i + 1);
	}
	return (0);
}

//values min 0 checked
static char	*trim(char const *s, size_t start, size_t end)
{
	size_t	index;
	char	*ret;

	index = 0;
	ret = malloc(end - start + 1);
	if (!ret)
		return (NULL);
	while (start + index < end)
	{
		ret[index] = s[start + index];
		index ++;
	}
	ret[index] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	strlen;

	strlen = 0;
	while (set[strlen])
		strlen++;
	start = m_start(s1, set);
	end = m_end(s1, set);
	if (start >= end)
	{
		return (trim(s1, 0, 0));
	}
	return (trim(s1, start, end));
}
