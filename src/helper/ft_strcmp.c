#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;
	unsigned char *ptr_s1;
	unsigned char *ptr_s2;

	i = 0;
	ptr_s1 = (unsigned char *) s1;
	ptr_s2 = (unsigned char *) s2;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (ptr_s1[i] - ptr_s2[i]);
}