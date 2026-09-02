#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//TODO
//chdir
//getcwd

int main(int c, char **vec, char **envp)
{
/* 	if (c > 0)
	{
		if (chdir("..") != 0)
		{
			vec = NULL;
			char buf[1024];
			getcwd(buf, 1024);
			printf("%s\n", buf);
		}
		else
			printf("unav\n");
	}
 */
	if (c < 0)
		return (0);
	char buf[1024]; int i = 0;

	char *co_pwd[2];
	co_pwd[0] = getenv("PWD"); co_pwd[1] = getenv("OLDPWD");

	getcwd(buf, 1024);
	printf ("%s\nC:%s\nO:%s\n---\n", buf, getenv("PWD"), getenv("OLDPWD"));
	i = chdir(vec[1]);	//changes current path to rel or abs path -xsymlink
/*
there needs to be a way to set envp. how do we? 
*/
	//sleep(10);
	perror("cdTest");
	// if (access(".", F_OK) == -1)
	// 	i = 1;
	// else if (access(".", R_OK) == -1)
	// 	i = 2;
	getcwd(buf, 1024);
	printf ("%s : %i\n", buf, i);
	printf ("%s\nC:%s\nO:%s\n---\n", buf, getenv("PWD"), getenv("OLDPWD"));
	if (vec[2])
		chdir(vec[2]);
	perror("cdTest");
	getcwd(buf, 1024);
	printf ("%s : %i\n", buf, i);
	printf ("%s\nC:%s\nO:%s\n---\n", buf, getenv("PWD"), getenv("OLDPWD"));
	if (vec[3])
		chdir(vec[3]);
	perror("cdTest");
	getcwd(buf, 1024);
	return (printf ("%s : %i\n", buf, i), 100);

/* 	char	buf[4096];

	if (c && vec)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			perror("msh_pwd");
			#include <errno.h>
			return (errno);
		}
		printf("%s\n", buf);
		return (0);

	}
*/
/* 	if (c > 2)
		return (printf("msh: cd: too many arguments\n"), 1);
	if (c == 2)
	{
		if (access(vec[1], F_OK))
			return (printf("msh: cd: %s: No such file or directory\n",
					vec[1]), 1);
		else if (access(vec[1], R_OK))
			return (printf("msh: cd: %s: Permission denied\n", vec[1]), 1);

	}
	printf("%s\n", *(envp + 4));
 */
}