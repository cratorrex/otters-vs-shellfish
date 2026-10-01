/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:19:59 by thtay             #+#    #+#             */
/*   Updated: 2026/10/01 17:23:59 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static int	isvalid_exit_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

/* Note: return value is the shell exit status, handle later
	CTRL^D should call this function
*/
long	msh_exit(t_shell *shell, char **av)
{
	int		argc;
	long	status;

	argc = get_argc(av);
	printf("exit\n");
	if (argc == 1)
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!isvalid_exit_arg(av[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", av[1]);
		shell->should_exit = 1;
		return (2);
	}
	if (argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	status = ft_atol(av[1]);
	shell->should_exit = 1;
	return ((unsigned char) status);
}
