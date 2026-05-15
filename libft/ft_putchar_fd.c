/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:04:47 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:04:48 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// write
//
// match putc (man3 puts fputc)
// >> write2 and write3 should be used for reference
// >> ssize_t if negative is an error :O 
// >> >> case: do nothing.
//
// file descriptor 
// echo 'c' >> fd (1 >> STDOUT)
//
// works as append 
// >> example if passed as the fd returned from the open() function
//

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
