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

static char	*mhd_expand_heredoc(char *string /*, env*/)
{
	return string;
}

//if delim has quotes there should be a notice of it.
//mode0 means we expand environment
//mode1 means the delim was quoted 
// ret_fd = open("/tmp", __O_TMPFILE | O_RDWR , 0777);
int	msh_pxheredoc(char *delimiter, int mode /*, env*/)
{
	char	*ptr;
	int		ret_fd;

	ret_fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (ret_fd > 2)
	{
		ptr = get_next_line(0);
		if (!ptr || ft_strncmp(ptr, delimiter, ft_strlen(delimiter)) == 0)
		{
			if (!ptr)
				printf("msh: warning: here-document delimited by end-of-file\
(wanted `%s')\n", delimiter);
			if (!ptr || ft_strlen(ptr) - 1 == ft_strlen(delimiter))
				break ;
		}
		if (mode == 0)
			ptr = mhd_expand_heredoc(ptr);
		ft_putstr_fd(ptr, ret_fd);
		free(ptr);
	}
	if (ptr != NULL)
		free(ptr);
	close(ret_fd);
	ret_fd = open(".tmp", O_RDWR);
	return (ret_fd);
}
