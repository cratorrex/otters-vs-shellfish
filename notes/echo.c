#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	mecho_ncheck(char *string)
{
	if (string)
	{
		if(*string == '-')
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
						return (1);
					else
						break ;
				}
			}
		}
	}
	return (0);
}

static void	mecho_print(char *string)
{
	while (string)
	{
		if (*string == 0)
			break ;
		write(1, string, 1);
		string ++;
	}
}

int	msh_echo(int count, char **string)
{
	int	nflag;

	nflag = mecho_ncheck(string[0]);
	if (string && count > 0)
	{
		if (nflag == 1)
		{
			string ++;
			count --;
		}
		while (count > 0)
		{
			mecho_print(*string);
			string ++;
			count --;
			if (count > 0)
				write(1, " ", 1);
		}
	}
	if (nflag == 0)
		write(1, "\n", 1);
	return (0); 
}

int main(int c, char **v)
{
	if (c >= 1)
		msh_echo(c - 1, v + 1);
}
