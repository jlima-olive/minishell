/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:20:43 by jlima-so          #+#    #+#             */
/*   Updated: 2025/07/25 15:18:03 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	keep[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*ret;
	int			i;

	if (BUFFER_SIZE <= 0 || fd >= FOPEN_MAX || fd < 0)
		return (NULL);
	i = 1;
	if (*keep[fd] == '\0')
		i = zero_read(fd, keep[fd]);
	if (i < 1 && (*keep[fd] == '\0' || !check(keep[fd])))
		return (NULL);
	ret = ft_gln_strjoin(NULL, keep[fd]);
	if (ret == NULL)
		return (NULL);
	while (i && check(ret))
	{
		i = zero_read(fd, keep[fd]);
		if (i < 1)
			break ;
		ret = ft_gln_strjoin(ret, keep[fd]);
		if (ret == NULL)
			return (NULL);
	}
	next_lines(keep[fd]);
	return (ret);
}
