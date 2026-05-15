/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:05:28 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:05:30 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// write
//
// the number 9 is char '9'
// not ascii 9 ('\h')
//
// Using ITOA means it must be freed.
//

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (fd < 0)
		return ;
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	digit = ((n % 10) + '0');
	write (fd, &digit, 1);
	return ;
}
