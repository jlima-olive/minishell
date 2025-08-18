/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:18:43 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:11:07 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check(char ch, const char *charset)
{
	int	ind;

	ind = 0;
	while (charset[ind])
	{
		if (charset[ind] == ch)
			return (1);
		ind++;
	}
	return (0);
}

static int	total_len(const char *str, const char *set)
{
	int	ind;
	int	total;

	total = 0;
	ind = -1;
	while (str[++ind] && ft_check (str[ind], set))
		total++;
	if (str[ind] == '\0')
		return (total);
	ind = ft_strlen(str);
	while (--ind >= 0 && ft_check (str[ind], set))
		total++;
	return (total);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ind;
	int		ind2;
	int		total;
	char	*ret;

	ind = 0;
	ind2 = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup((char *)s1));
	total = ft_strlen(s1) - total_len(s1, set);
	ret = ft_calloc(total + 1, 1);
	if (ret == NULL)
		return (NULL);
	while (ft_check(s1[ind], (char *)set) && s1[ind])
		ind++;
	while (s1[ind] && ind2 < total)
		ret[ind2++] = s1[ind++];
	return (ret);
}
