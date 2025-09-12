/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:36:11 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/12 15:48:10 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_join_matrix(char **mat, int indv, int ind, int total)
{
	char	*ret;

	while (mat[indv])
	{
		while (mat[indv][ind])
			ind++;
		total += ind + 1;
		indv++;
	}
	ret = ft_calloc(total, sizeof(char));	
	if (ret == NULL)
		return (NULL);
	ind = 0;
	indv = -1;
	while (mat[++indv])
	{
		while (*mat[indv])
		{
			ret[ind] = *mat[indv];
			(mat[indv])++;
		}
		if (mat[indv + 1] != NULL && *mat[indv + 1] != '\0')
			ret[ind] = ' ';
	}
	return (ret);
}
