/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:24:50 by thtay             #+#    #+#             */
/*   Updated: 2025/12/05 17:24:52 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//free

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*prev;

	iter = *lst;
	while (iter)
	{
		prev = iter;
		if (iter -> content && del)
			del(iter -> content);
		iter = iter -> next;
		free(prev);
	}
	*lst = NULL;
}
