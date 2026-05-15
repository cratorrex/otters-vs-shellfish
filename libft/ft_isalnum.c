/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:33:22 by thtay             #+#    #+#             */
/*   Updated: 2025/11/17 21:33:43 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// The 'is' series checks individual characters at a time
//

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
