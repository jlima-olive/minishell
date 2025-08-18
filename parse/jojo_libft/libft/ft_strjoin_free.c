/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:32:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/08/18 11:55:15 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	char	*ret;

	ret = ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1, 1);
	if (ret == NULL)
		return (free (s2), free (s1), NULL);
	ret = ft_strcpy(ret, (char *)s1);
	ret = ft_strcat(ret, (char *)s2);
	if (flag != 2)
		free (s1);
	if (flag != 1)
		free (s2);
	return (ret);
}
