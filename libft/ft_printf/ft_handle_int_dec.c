/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_int_dec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:51:30 by thtay             #+#    #+#             */
/*   Updated: 2025/12/30 15:51:31 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_int(int num)
{
	char	*val;
	size_t	len;

	val = ft_itoa(num);
	len = ft_strlen(val);
	free(val);
	ft_putnbr_fd(num, 1);
	return (len);
}
