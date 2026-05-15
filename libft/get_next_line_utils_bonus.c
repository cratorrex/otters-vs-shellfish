/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:21:43 by thtay             #+#    #+#             */
/*   Updated: 2025/12/19 21:21:44 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read, malloc, free
//
// helper functions go here
//
// strjoin, strdup, strchr, bud_trim, strlen

#include "libft.h"

//here we go again...
ssize_t	gnl_strlen(const char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//both have been malloced. so they have to also be freed.
//malloc a new string.
//stash is now s1 cat s2.
char	*gnl_strljoin(char *s1, char *s2)
{
	ssize_t	init;
	ssize_t	cat;
	char	*join;

	init = 0;
	cat = 0;
	join = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1[init])
	{
		join[init] = s1[init];
		init++;
	}
	while (cat < gnl_strlen(s2))
	{
		join[init + cat] = s2[cat];
		cat++;
	}
	join[init + cat] = '\0';
	if (gnl_strlen(s1) || s1 != NULL)
		free(s1);
	return (join);
}

//find \n
//returns the index (idx)
ssize_t	gnl_memnchr(char *str, ssize_t size)
{
	ssize_t	i;

	if (size <= 0)
		return (size);
	i = 0;
	while (i < size)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i);
		i++;
	}
	return (size);
}

//colon three c comma question mark
char	*gnl_strdup(char *str)
{
	ssize_t	i;
	char	*new;

	new = malloc(gnl_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
