/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:05:00 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:05:01 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// write
//
// output string *s to fd
// may need strlen
//

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (fd < 0)
		return ;
	while (s[len])
		len++;
	write(fd, s, len);
}
