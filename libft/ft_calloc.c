/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:31 by thtay             #+#    #+#             */
/*   Updated: 2025/11/22 17:20:32 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc
//
// CRASH IF (ERROR, RETURN NULL)
// nmemb = SIZE_MAX / size;
//
// calloc sets all bytes to '\0', malloc does not << ref man
//
// members X size
//

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;

	if (nmemb == 0 || size == 0)
	{
		new = malloc(0);
		if (!new)
			return (NULL);
		return (new);
	}
	if ((ssize_t) nmemb < 0 || (ssize_t) size < 0)
		return (NULL);
	if (nmemb > INT_MAX / size)
		return (NULL);
	new = malloc(nmemb * size);
	if (!new)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}
