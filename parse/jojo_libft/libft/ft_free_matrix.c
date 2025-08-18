/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:46:11 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:05:22 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_matrix(char **matrix)
{
	int	ind;

	ind = -1;
	while (matrix[++ind])
		free(matrix[ind]);
	free (matrix);
}
