/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:40:24 by thtay             #+#    #+#             */
/*   Updated: 2025/11/18 11:40:35 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// The 'is' series checks individual characters at a time
//
// ascii goes from 0 to 127
// feeding through argc argv validates this
// feeding through normal input also validates this
//

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
