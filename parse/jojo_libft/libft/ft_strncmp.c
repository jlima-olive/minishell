/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:58:30 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 12:47:33 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			ind;
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	ind = 0;
	while (str1[ind] && str2[ind] && str1[ind] == str2[ind] && ind < n - 1)
		ind++;
	return (str1[ind] - str2[ind]);
}
