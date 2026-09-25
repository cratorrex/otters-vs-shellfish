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
static int	mecho_lenstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//if print success return (aka exit) 0
//option "-n"
static int	mecho_ncheck(char *string, int *count)
{
	if (string)
	{
		if (*string == '-')
		{
			string ++;
			if (*string == 'n')
			{
				string ++;
				while (string)
				{
					if (*string == 'n')
						string ++;
					else if (*string == 0)
						return (-- (*count), 1);
					else
						break ;
				}
			}
		}
	}
	return (0);
}

//print literal as all tokens have been parsed.
static void	mecho_print(char *string)
{
	while (string)
	{
		if (string == NULL || !*string)
			break ;
		write(1, string, 1);
		string ++;
	}
}

int	msh_echo(t_shell *shell, char **string)
{
	int	nflag;
	int	count;

	count = mecho_lenstr(string);
	nflag = mecho_ncheck(string[0], &count);
	if (string)
	{
		if (nflag == 1)
			string ++;
		while (string && count > 0)
		{
			mecho_print(*string);
			string ++;
			count --;
			if (count > 0)
				write(1, " ", 1);
			else
				break ;
		}
	}
	if (nflag == 0)
		write(1, "\n", 1);
	shell->exit_status = 0;
	return (0);
}
