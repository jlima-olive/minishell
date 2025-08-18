/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:43:43 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:10 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	ind;

	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
	ind = -1;
	while (src[++ind] != '\0')
		dest[ind] = src[ind];
	dest[ind] = '\0';
	return (dest);
}
