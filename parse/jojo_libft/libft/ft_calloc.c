/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:58:22 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:05:15 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	ind;

	ind = -1;
	if (nmemb == 0 || size == 0 || ind / nmemb >= size)
	{
		ret = malloc(size * nmemb);
		if (ret == NULL)
			return (0);
		ind = 0;
		ft_bzero(ret, size * nmemb);
		return (ret);
	}
	return (NULL);
}
