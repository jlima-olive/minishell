/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:24:06 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/20 00:24:07 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_aspas(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*removed;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_it(str, '"') - count_it(str, '\'');
	removed = malloc(len + 1);
	if (!removed)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			removed[j++] = str[i];
		i++;
	}
	removed[j] = '\0';
	return (removed);
}

char	*remove_it(char *str, int c)
{
	int		i;
	int		j;
	int		count;
	char	*removed;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	count = count_it(str, c);
	removed = malloc(ft_strlen(str) + 1 - count);
	if (!removed)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			removed[j] = str[i];
			j++;
		}
		i++;
	}
	removed[j] = '\0';
	return (removed);
}

char	*odd_aspas(char *str, char c)
{
	int		count;
	char	*result;
	char	*input;
	char	*tmp;

	count = count_it(str, c);
	result = ft_strdup(str);
	while (count % 2 != 0)
	{
		input = readline("> ");
		if (!input)
			continue ;
		tmp = result;
		result = ft_strjoin(result, input);
		free(tmp);
		free(input);
		count = count_it(result, c);
	}
	return (result);
}

char	*aspas(char *str, int c)
{
	char	*with_closed_quotes;
	char	*cleaned;

	if (!str)
		return (NULL);
	with_closed_quotes = odd_aspas(str, c);
	cleaned = remove_it(with_closed_quotes, c);
	free(with_closed_quotes);
	return (cleaned);
}
