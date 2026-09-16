#include "minishell.h"

/*display token for debugging, clean up later*/
void display_tokens(t_token *tokens)
{
	int index = 0;
	while (tokens)
	{
		index++;
		printf("token %d value = %s | type = %d\n", index, tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int		i;
	int		cmd_index;
	t_redir	*redir;

	cmd_index = 0;
	while (cmd)
	{
		printf("\n========== CMD %d ==========\n", cmd_index);

		printf("Arguments:\n");
		if (!cmd->av)
			printf("  (none)\n");
		else
		{
			i = 0;
			while (cmd->av[i])
			{
				printf("  av[%d] = \"%s\"\n", i, cmd->av[i]);
				i++;
			}
		}

		printf("Redirections:\n");
		if (!cmd->redirs)
			printf("  (none)\n");
		else
		{
			redir = cmd->redirs;
			while (redir)
			{
				printf("  type = %d, target = \"%s\"\n",
					redir->type, redir->target);
				redir = redir->next;
			}
		}

		printf("============================\n");

		cmd = cmd->next;
		cmd_index++;
	}
}

void print_env(char **env, char *message)
{
    int i = 0;
    printf("%s\n", message);
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

