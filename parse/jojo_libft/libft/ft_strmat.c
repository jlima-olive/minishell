/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:20:20 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:40 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmat(char **matrix, char *s)
{
	int	ind;

	ind = -1;
	while (matrix[++ind])
		if (ft_strstr(matrix[ind], s))
			return (matrix[ind]);
	return (NULL);
}
