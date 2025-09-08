#include "../sigma_minishell.h"

int	find_tokens(char *str, t_token tokens)
{
	if (ft_matnstr(tokens.dtokens, str, 2))
		return (2);
	if (ft_matnstr(tokens.stokens, str, 1))
		return (1);
	return (0);
}

static int	word_count_aux(int ind, char *str, t_token tokens, char **sep)
{
	char	*sep_found;

	while (find_tokens(str + ind, tokens) == 0 && str[ind] && \
		(str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		sep_found = ft_matnstr(sep, str + ind, 1);
		if (sep_found && ++ind)
		{
			while (str[ind] != *sep_found && str[ind])
				ind++;
			if (str[ind] == '\0')
				return (-(*sep_found));
			ind++;
		}
		else
			ind++;
	}
	return (ind);
}

int	word_count(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		count;
	int		token_found;

	ind = 0;
	count = 0;
	while (str[ind])
	{
		while (str[ind] == ' ' || str[ind] == '\t' || str[ind] == '\n')
			ind++;
		if (str[ind] == '\0')
			return (count);
		token_found = find_tokens(str + ind, tokens);
		if (token_found)
		{
			count++;
			ind += token_found;
		}
		else if (find_tokens(str + ind, tokens) == 0 && str[ind] && \
			(str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n') && ++count)
			ind = word_count_aux( ind, str, tokens, sep);
		if (ind < 0)
			return (ind);
	}
	return (count);
}

int parsing_strlen_aux(int ind, char *str, t_token tokens, char **sep)
{
	char	*sep_found;
	
	while (find_tokens(str + ind, tokens) == 0 && str[ind] \
		&& (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		sep_found = ft_matnstr(sep, str + ind, 1);
		if (sep_found)
		{
			ind++;
			while (str[ind] != *sep_found && str[ind])
				ind++;
			if (str[ind] == '\0')
				return (-(*sep_found));
			ind++;
		}
		else
			ind++;
	}
	return (ind);
} 

int	parsing_strlen(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		token_found;

	ind  = 0;
	token_found = find_tokens(str + ind, tokens);
	if (token_found)
		return (token_found);
	else if (find_tokens(str + ind, tokens) == 0 \
		&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		return (parsing_strlen_aux(ind, str, tokens, sep));
	return (0);
}
