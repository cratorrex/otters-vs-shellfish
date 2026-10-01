/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:15:38 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:16:12 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rl_gets(void)
{
	char	*line_read;

	line_read = readline("minishell>");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	free_line_buffer(char **line_buffer)
{
	if (*line_buffer)
	{
		free(*line_buffer);
		*line_buffer = NULL;
	}
}
