/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:18:14 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:07:01 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	ind;

	ind = -1;
	if (dest > src)
		while (n-- > 0)
			((char *)dest)[n] = ((char *)src)[n];
	else
		while (++ind < n)
			((char *)dest)[ind] = ((char *)src)[ind];
	return (dest);
}
