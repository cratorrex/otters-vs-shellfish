/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:23:38 by thtay             #+#    #+#             */
/*   Updated: 2026/10/08 16:23:40 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_export_variable(char *var)
{
	char	*equal;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		printf("declare -x %s\n", var);
		return ;
	}
	printf("declare -x ");
	printf("%.*s", (int)(equal - var), var);
	printf("=\"%s\"\n", equal + 1);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
