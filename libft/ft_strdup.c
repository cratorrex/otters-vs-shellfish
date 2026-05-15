/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:07:26 by thtay             #+#    #+#             */
/*   Updated: 2025/11/22 17:07:28 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// malloc(size_t n+1)
// else return (NULL);
//
// free() in int main()
//

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*new;

	i = 0;
	while (s[i])
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
