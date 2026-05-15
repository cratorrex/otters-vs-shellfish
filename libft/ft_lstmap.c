/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:25:40 by thtay             #+#    #+#             */
/*   Updated: 2025/12/05 17:25:41 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//malloc, free

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;
	t_list	*add;

	ret = NULL;
	while (lst && f)
	{
		add = f(lst -> content);
		new = ft_lstnew(add);
		if (!new)
		{
			if (add && del)
				del(add);
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
		lst = lst -> next;
	}
	if (lst == NULL)
		return (ret);
	return (NULL);
}
