/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:29:20 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:06:19 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*temp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	ret = ft_lstnew(f(lst->content));
	if (ret == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
		{
			ft_lstclear (&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, temp);
		lst = lst->next;
	}
	return (ret);
}
