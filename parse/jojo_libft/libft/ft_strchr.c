/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:05:05 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:04 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp != (char)c && *temp)
		temp++;
	if (*temp == (char)c)
		return (temp);
	return (NULL);
}
