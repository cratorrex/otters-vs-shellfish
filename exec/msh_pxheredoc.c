/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 18:18:31 by thtay             #+#    #+#             */
/*   Updated: 2026/09/08 18:18:34 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if delim has quotes there should be a notice of it.
//mode0 means we expand environment
//mode1 means the delim was quoted 
int	msh_pxheredoc(char *delimiter/* , int mode */)
{
	char	*ptr;
	int		ret_fd;

	ret_fd = open("/tmp", __O_TMPFILE | O_RDWR);
	if (ret_fd < 0)
		return (-1);
	while (1)
	{
		ptr = get_next_line(0);
		if (!ptr || ft_strncmp(ptr, delimiter, ft_strlen(delimiter)) == 0)
		{
			if (ft_strlen(ptr) - 1 == ft_strlen(delimiter))
				break ;
			{/*expansion stuff here*/}
		}
		ft_putstr_fd(ptr, ret_fd);
		free(ptr);
	}
	if (ptr != NULL)
		free(ptr);
	return (ret_fd);
}

/*
cat << a << b 

jdgsjdfgjsdgjfsdf
fjskdgkshd
dhfaghsgasd
a >> \0 EOF?
jkshdfkjshdkjhas
ajdhakjshdkjah
fjhkasa
b >> \0 EOF?

*/