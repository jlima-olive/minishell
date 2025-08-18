/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:43:03 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:09:58 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	ind;
	int	ind2;

	if (dest == NULL)
		return (NULL);
	ind = -1;
	ind2 = ft_strlen(dest);
	if (src == NULL)
		return (dest);
	while (src[++ind] != '\0')
		dest[ind2++] = src[ind];
	dest[ind2] = '\0';
	return (dest);
}
