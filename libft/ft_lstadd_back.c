/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:24:23 by thtay             #+#    #+#             */
/*   Updated: 2025/12/05 17:24:26 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*c_node;

	c_node = *lst;
	if (!c_node)
	{
		*lst = new;
		return ;
	}
	while (c_node -> next != NULL)
	{
		c_node = c_node -> next;
	}
	c_node -> next = new;
	return ;
}
