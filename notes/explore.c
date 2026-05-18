#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *bracket;
	char *prompt = ">";
	bracket = readline(prompt);
	printf ("\n||%s%s||\n", prompt, bracket);
	free(bracket);
}