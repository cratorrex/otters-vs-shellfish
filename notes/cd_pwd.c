#include <stdio.h>
#include <unistd.h>

//TODO
//chdir
//getcwd

int main(int c, char **vec)
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
	char buf[1024]; int i = 0;
	getcwd(buf, 1024);
	printf ("%s\n", buf);
	i = chdir(vec[1]);	//changes current path to rel or abs path
	sleep(10);
	if (access(".", F_OK) == -1)
		i = 1;
	else if (access(".", R_OK) == -1)
		i = 2;
	getcwd(buf, 1024);
	printf ("%s : %i\n", buf, i);
}