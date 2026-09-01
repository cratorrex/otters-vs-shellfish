#include "minishell.h"

static char	*append_char(char *result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';

	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

static char	*append_string(char *result, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(result, str);
	free(result);
	return (tmp);
}

static int	handle_quote(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && !(*double_quote))
	{
		*single_quote = !(*single_quote);
		return (1);
	}
	if (c == '"' && !(*single_quote))
	{
		*double_quote = !(*double_quote);
		return (1);
	}
	return (0);
}

static char	*handle_variable(char *str, int *i,
				char *result, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(str, i, shell);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}

	result = append_string(result, expanded);
	free(expanded);

	return (result);
}

char	*expand_word(char *str, t_shell *shell)
{
	int		i;
	int		single_quote;
	int		double_quote;
	char	*result;

	i = 0;
	single_quote = 0;
	double_quote = 0;

	result = ft_strdup("");
	if (!result)
		return (NULL);

	while (str[i])
	{
		if (handle_quote(str[i], &single_quote, &double_quote))
			i++;
		else if (str[i] == '$' && !single_quote)
			result = handle_variable(str, &i, result, shell);
		else
		{
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
			i++;
		}

		if (!result)
			return (NULL);
	}

	return (result);
}