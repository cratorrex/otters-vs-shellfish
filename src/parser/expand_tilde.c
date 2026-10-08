/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:31:42 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 13:31:44 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(char *home, int *i, char slash)
{
	int	n;

	n = 0;
	if (!home)
	{
		ft_putstr_fd("msh: HOME not set\n", 2);
		return (NULL);
	}
	if (slash == 0 || slash == '/')
	{
		*i = *i + 1;
		while (home[n])
		{
			if (home[n] != '/' && home[n + 1] == 0 && slash == 0)
				return (append_char(home, '/'));
			else
				n++;
		}
		return (home);
	}
	return (free(home), ft_strdup(""));
}
