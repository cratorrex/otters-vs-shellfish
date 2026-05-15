/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:07:51 by thtay             #+#    #+#             */
/*   Updated: 2025/11/18 15:07:53 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// The 'is' series checks individual characters at a time
//
// Printables go from 32 to 126
// 127 is DEL (unprintable)
//

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
