/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:36:11 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/22 01:54:38 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_join_matrix(char **mat, int indv, int ind, int total)
{
	char	*ret;
	int		indh;

	while (mat[indv])
	{
		indh = 0;
		while (mat[indv][indh])
			indh++;
		total += indh + 1;
		indv++;
	}
	ret = ft_calloc(total, sizeof(char));	
	if (ret == NULL)
		return (NULL);
	ind = 0;
	indv = -1;
	while (mat[++indv])
	{
		indh = 0;
		while (mat[indv][indh])
		{
			ret[ind] = mat[indv][indh];
			indh++;
			ind++;
		}
		if (mat[indv + 1] != NULL && mat[indv + 1][0] != '\0')
		{
			ret[ind] = ' ';
			ind++;
		}
	}
	return (ret);
}
