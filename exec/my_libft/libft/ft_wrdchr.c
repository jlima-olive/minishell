/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrdchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:40:04 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/21 16:40:46 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_wrdchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp != (char)c && *temp && *temp != ' ')
		temp++;
	if (*temp == (char)c)
		return (temp);
	return (NULL);
}
