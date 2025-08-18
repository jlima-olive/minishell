/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:42:14 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/12 12:35:10 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	zero_read(int fd, char *keep)
{
	int	ind;

	ind = read(fd, keep, BUFFER_SIZE);
	if (ind >= 0)
		keep[ind] = '\0';
	return (ind);
}

void	next_lines(char *ret)
{
	int	ind;
	int	add;

	add = ft_gnl_strlen(ret);
	ind = 0;
	while (ret[ind + add] && ret[ind])
	{
		ret[ind] = ret[ind + add];
		ind++;
	}
	if (ret[ind + add] == '\0')
		ret[ind] = '\0';
}

int	ft_gnl_strlen(char *str)
{
	int	ind;

	ind = 0;
	while (str[ind])
	{
		ind++;
		if (str[ind - 1] == '\n')
			return (ind);
	}
	return (ind);
}

char	*ft_gln_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		ind;

	if (s1 == NULL)
	{
		s1 = malloc (1);
		s1[0] = '\0';
	}
	ret = malloc (ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1);
	if (ret == NULL)
		return (free (s1), NULL);
	ind = -1;
	while (s1[++ind])
		ret[ind] = s1[ind];
	free (s1);
	while (*s2)
	{
		ret[ind] = *(s2);
		ind++;
		s2++;
		if (*(s2 - 1) == '\n')
			break ;
	}
	ret[ind] = '\0';
	return (ret);
}

int	check(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}
