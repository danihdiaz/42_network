/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:53:50 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/29 18:54:19 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	void	*cont;
	t_list	*lista;

	lista = NULL;
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
		{
			ft_lstclear(&lista, del);
			return (NULL);
		}
		new = ft_lstnew(cont);
		if (!new)
		{
			del(cont);
			ft_lstclear(&lista, del);
			return (NULL);
		}
		ft_lstadd_back(&lista, new);
		lst = lst->next;
	}
	return (lista);
}
