/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:05:17 by thtay             #+#    #+#             */
/*   Updated: 2025/11/24 13:05:18 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// write
//
// echo { *s + '\n' } >> fd
//

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (fd < 0)
		return ;
	while (s[len])
		len++;
	write(fd, s, len);
	write(fd, &"\n", 1);
}
