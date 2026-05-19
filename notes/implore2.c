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
