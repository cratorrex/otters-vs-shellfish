/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:04:32 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:04:33 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// foreach in *s { function *f(); }
// string iterate
// >> index, string
//
// 	if c[i] > 32
//  write 1, &c[i], 1
//

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
	return ;
}
