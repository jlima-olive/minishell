/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnmat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 07:29:57 by jlima-so          #+#    #+#             */
/*   Updated: 2025/08/18 16:21:37 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_matnstr(char **matrix, char *s, int n)
{
	int	ind;

	ind = -1;
	while (matrix[++ind])
		if (ft_strnstr(s, matrix[ind], n))
			return (matrix[ind]);
	return (NULL);
}

/* char	*ft_strnstr(char **matrix, char *s, int n)
{
	int	ind;

	ind = -1;
	while (matrix[++ind])
		if (ft_strncmp(s, matrix[ind], n) == 0)
			return (matrix[ind]);
	return (NULL);
}
 */