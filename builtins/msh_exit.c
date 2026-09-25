/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:19:59 by thtay             #+#    #+#             */
/*   Updated: 2026/08/14 20:20:00 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if ^D and exit {?num}
long	ft_atol(const char *str)
{
	long	sign;
	long	sum;
	int		i;

	sum = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
		break ;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sum * sign);
}

static int	get_argc(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int contains_numeric_only(char *num)
{
    int i;

    i = 0;
    while (num[i])
    {
        if (!(num[i] >= '0' && num[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

int	msh_exit(t_shell *shell, char **av)
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
	if (!contains_numeric_only(av[1]))
	{
		printf("msh: exit: %s: numeric argument required\n", av[1]);
		shell->should_exit = 1;
		return (2);
	}
	if (argc > 2)
	{
		printf("msh: exit: too many arguments\n");
		return (1);
	}
	status = ft_atol(av[1]);
	shell->should_exit = 1;
	return ((unsigned char)status);
}