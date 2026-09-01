/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:10:38 by thtay             #+#    #+#             */
/*   Updated: 2026/08/10 20:10:39 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sign = 0;

//uses the signal() function
//```
//^C exit 2 (130)
//^\ exit 3 (131)
//```

//init and then switch to msig_interactive
void	msh_sig_init(void)
{
	// struct sigaction	act;

	// sigaction(SIGINT, &act, NULL);
	// sigaction(SIGQUIT, &act, NULL);
}

//if readline then use this
void	msig_interactive(void)
{
	//kill(this, 0) basically does nothing other than
	//validating the process
}

//if in child program/process, use this. remember to swap back.
void	msig_prog_proc(void)
{

}

// void main ()
// {
// 	printf("hi");
// }

/*
Signal Action function understanding of documentation

takes int SIGNAL, and the SIGACTION structure,
which holds a sighandler structure and a mask.

The mask SIGSET should be assigned by the ADDSET and EMPTYSET functions.
ADDSET appends the signal to the set
EMPTYSET clears the set
*/