/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:28:40 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:11:05 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	indl;
	size_t	indb;

	indb = 0;
	if (big == NULL || little == NULL)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (big[indb])
	{
		indl = 0;
		while (big[indb + indl] == little[indl])
		{
			indl++;
			if (little[indl] == '\0')
				return ((char *)big + indb);
		}
		indb++;
	}
	return (NULL);
}
