/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:21:17 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 17:22:10 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_shell *shell, char **av)
{
	if (!shell || !av)
		return (1);
	if (av[1])
	{
		ft_putendl_fd("msh: env: too many arguments", 2);
		return (1);
	}
	print_env(shell->env);
	return (0);
}
