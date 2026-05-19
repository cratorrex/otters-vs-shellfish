#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//volatile sig_atomic_t	g_sign = 0;
sig_atomic_t	g_sign = 0;

//void (*signal(int sig, void (*func)(int)))(int);
//this being the func
static void	signaler(int sign)
{
	g_sign = sign;
	printf("\n--%i--\n", (int)sign);
}

//sample function to "simulate" handling signals
//f'ln 8 - 10 reads the stdin for a 2 digit number 
// >> RMB THIS IS JUST A DEBUG SHOW
// >>>> everything underneath is... i guess just see...
//if a signal is sent in (say Ctrl-C), signaler() will trigger
int	main(void)
{
	signal(2, signaler); //SIGINT
	signal(3, signaler); //SIGQUIT

	signal(11, signaler); //SIGSEGV
	signal(15, signaler); //SIGTERM
	//signal(SIGINT, signaler);

	char tri[3] = "11";
	read(0,tri,2);
	raise(atoi(tri));
	printf("HELLO WORLD! %i\n", (int)g_sign);
	read(0,tri,2);
	read(0,tri,2);
	read(0,tri,2);
	printf("HELLO WORLD! %i\n", (int)g_sign);

	return (0);
}

/* 
From wikipedia

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t status = 0;

static void catch_function(int signo) {
    status = signo;
}

int main(void) {
    // Set above function as signal handler for the SIGINT signal:
    if (signal(SIGINT, catch_function) == SIG_ERR) {
        fprintf(stderr, "An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }
    printf("Raising the interactive attention signal.");
    if (raise(SIGINT)) {
        fprintf(stderr, "Error raising the signal.\n");
        return EXIT_FAILURE;
    }
    if (status == SIGINT) {
        printf("Interactive attention signal caught.");
    }
    printf("Exiting.");
    return EXIT_SUCCESS;
    // exiting after raising signal
}
 */