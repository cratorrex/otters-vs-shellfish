/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:24:41 by thtay             #+#    #+#             */
/*   Updated: 2025/12/05 17:24:43 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// **lst == start of list
// add *new to **lst
// if lst doesn't exist, then just ln 15
//

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
		new -> next = *lst;
	*lst = new;
}
