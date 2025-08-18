/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:06:25 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/20 06:39:52 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	real_wrd_count(char *str, int ind, int count)
{
	while (*str)
	{
		ind = 0;
		while (*str && *str == ' ')
			str++;
		if (*str && *str != '\'')
		{
			while (*str && *str != ' ' && *str != '\'')
				str++;
			count++;
		}
		if (*str && *str == '\'')
		{
			str++;
			while (*str && *str != '\'')
			{
				str++;
				ind = 1;
			}
			if (ind)
				count++;
			str++;
		}
	}
	return (count);
}

static int	wrd_count(char *str)
{
	int	ind;
	int	count;

	if (str == NULL)
		return (0);
	ind = -1;
	count = 0;
	while (str[++ind])
		if (str[ind] == '\'')
			count++;
	if (count % 2)
		return (0);
	count = real_wrd_count(str, ind, 0);
	return (count);
}

static int	next_str(char *str)
{
	int	ind;
	int	space;

	space = 0;
	ind = 0;
	if (str[ind] != '\'')
		while (str[ind] && str[ind] != ' ' && str[ind] != '\'')
			ind++;
	else if (str[ind] == '\'' && str[ind++])
	{
		while (str[ind] != '\'' && str[ind])
		{
			if (space == -1 && str[ind] == ' ')
				space = ind;
			ind++;
		}
		ind++;
		if (str[ind - 1] != '\'')
			ind = space;
	}
	return (ind);
}

static	char	**create_empty_mat(void)
{
	char	**ret;

	ret = malloc(2 * sizeof(char *));
	ret[1] = NULL;
	ret[0] = malloc(1);
	ret[0][0] = '\0';
	return (ret);
}

char	**pipex_split(char *str, char **ret, int count, int loop)
{
	int	ind;

	if (count == 0)
		count = wrd_count(str);
	if (count == 0)
		return (create_empty_mat());
	if (ret == NULL && loop == 0)
		ret = malloc((count + 1) * sizeof(char *));
	if (ret == NULL && loop == 0)
		return (NULL);
	ret[count - loop] = NULL;
	if (count == loop)
		return (ret);
	while (*str == ' ' && str)
		str++;
	ind = next_str(str) - ((*str == '\''));
	str += (*str == '\'');
	*ret = ft_strndup(str, ind - (ind - 1 > 0 && (str[ind - 1] == '\'')));
	if (*ret == NULL)
		return (ft_free_matrix_count(ret - loop, loop), NULL);
	while (*str == ' ' && str)
		str++;
	pipex_split (str + ind, ret + 1, count, loop + 1);
	return (ret);
}
