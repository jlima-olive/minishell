/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:01:11 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:38 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		ind;
	char	*ret;

	if (s == NULL || f == NULL)
		return (NULL);
	ret = (char *)ft_calloc(ft_strlen((char *)s) + 1, 1);
	if (ret == NULL)
		return (NULL);
	ind = -1;
	while (s[++ind])
		ret[ind] = f(ind, s[ind]);
	return (ret);
}
