/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:59:16 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:32 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	ind;
	size_t	ret;

	ind = 0;
	ret = (ft_strlen((char *)src));
	if (size == 0)
		return (ret);
	while (ind < size - 1 && src[ind])
	{
		dst[ind] = src[ind];
		ind++;
	}
	dst[ind] = '\0';
	return (ret);
}
