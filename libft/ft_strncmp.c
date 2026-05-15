/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:34:40 by thtay             #+#    #+#             */
/*   Updated: 2025/11/19 18:34:41 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// is string == string ? yesn't.
//

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while (c1[i] == c2[i] && i < (n - 1) && c1[i] != 0 && c2[i] != 0)
		i++;
	if (n == 0)
		return (0);
	return (c1[i] - c2[i]);
}
