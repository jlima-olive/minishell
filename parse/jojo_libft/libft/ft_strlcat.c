/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:12:29 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:30 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ind;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len + size);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (src_len + size);
	ind = 0;
	while (ind + dst_len < size - 1 && src[ind])
	{
		dst[dst_len + ind] = src[ind];
		ind++;
	}
	dst[dst_len + ind] = '\0';
	return (src_len + dst_len);
}
