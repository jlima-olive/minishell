/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:03:14 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:45 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(char *str, int ind)
{
	char	*ret;

	if (str == NULL)
		return (NULL);
	ret = ft_calloc (ind + 1, 1);
	while (ind--)
		ret[ind] = str[ind];
	return (ret);
}
