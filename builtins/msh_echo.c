/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 16:59:03 by thtay             #+#    #+#             */
/*   Updated: 2026/08/14 16:59:04 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Interpretation:
handle all parsed characters as string
subject indicates to only handle option "-n".
> first vector is checked if it's a valid -n
> no = print all vectors | yes = print next vector onwards
> end with newline if the flag is off else don't print.
> separation of vectors by a single space unless quoted.

>> f'n bash coded -nnnnnnnnnnnnnnnnnnnnnn as a valid -n
>> f'n bash coded -ntnnnnnnnnnnnnnnnnnnnn as invalid -n

backslash "\" character shall not be parsed by echo. so "\n"
will be treated as "\n"
> > and since the subject specifies not needing to handle "\",
> > the parsing logic should also apply "\n" (without quotes) as "\n".

Bash version following 5.1.16 on the school's computer.
*/

//seems like count is needed in some capacity,
//inb4 overrunning into unread territory

//if print success return (aka exit) 0
//option "-n"

static int	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	msh_echo(t_shell *shell, char **av)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	while (av[i] && is_n_option(av[i]))
	{
		nflag = 1;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			printf(" ");
	}
	if (!nflag)
		printf("\n");
	if (shell)
		shell->exit_status = 0;
	return (0);
}
