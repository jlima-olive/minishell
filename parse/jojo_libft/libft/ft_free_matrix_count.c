/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:54:51 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:05:19 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_matrix_count(char **mat, int count)
{
	if (mat == NULL)
		return ;
	while (count--)
		free (mat[count]);
	free(mat);
}
