/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:03:32 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:03:34 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc, free
//
// return array[]
// set, set, set {delim c} (end with \0)
//
// ERROR NULL

#include "libft.h"

static char	*alloc_small(char const *s, size_t size, size_t idx)
{
	char	*ret;
	size_t	incr;

	incr = 0;
	if (size == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	while (size > incr)
	{
		ret[incr] = s[idx + incr];
		incr++;
	}
	ret[incr] = '\0';
	return (ret);
}

static void	de_alloc(char **array, size_t word)
{
	while (word > 0)
	{
		free (array[word]);
		word--;
	}
	if (word == 0)
		free (array[word]);
	free (array);
}

//population increase
static char	**alloc_arr(char const *s, char c, char **array)
{
	size_t	size;
	size_t	prev;
	size_t	word;

	size = 0;
	prev = 0;
	word = 0;
	while (s[prev])
	{
		while (s[prev] == c)
			prev++;
		while (s[prev + size] != c && s[prev + size] != '\0')
			size++;
		array[word] = alloc_small(s, size, prev);
		if (array[word] == NULL && s[prev] != '\0')
		{
			de_alloc(array, word);
			return (NULL);
		}
		word++;
		prev = prev + size;
		size = 0;
	}
	return (array);
}

//return big array, ter '\0'
static char	**alloc_big(char const *s, char c)
{
	size_t	i;
	size_t	dcount;
	char	**big;

	dcount = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (s[i] != c)
				dcount++;
			i++;
		}
		if (s[i] != c)
			if (s[i - 1] == c)
				dcount++;
		i++;
	}
	big = malloc(sizeof(char *) * (dcount + 1));
	if (!big)
		return (NULL);
	big[dcount] = NULL;
	return (big);
}

// Count words, not delims >> malloc(count + 1)
// each pointer, malloc and print into... :thinking:
char	**ft_split(char const *s, char c)
{
	char	**array;

	array = alloc_big(s, c);
	if (array)
	{
		array = alloc_arr(s, c, array);
		if (array == NULL)
			return (NULL);
		return (array);
	}
	return (NULL);
}
