/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:00:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/11 15:44:03 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_matrix_nodes(char **mat)
{
	int	ind;
	
	ind = -1;
	while (mat[++ind])
		free(mat[ind]);
	*mat = NULL;	
}
