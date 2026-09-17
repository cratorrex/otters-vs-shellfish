#include "minishell.h"

int is_empty_prompt(const char *line_read)
{
	return (ft_strlen(line_read) == 0);
}

int is_only_space(const char *line_read)
{
	int i;
	int len;

	i = 0;
	while (line_read[i] && line_read[i] == ' ')
		i++;
	len = ft_strlen(line_read);
	if (len == i)
		return (1);
	return (0);
}

