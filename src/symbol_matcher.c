#include "minishell.h"

int isfound_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int is_delimiter(char c)
{
    return (c == ' ' || c == '\t');
}

int is_operator(char c)
{
    return (c == '|' || c == '>' || c == '<');
}



