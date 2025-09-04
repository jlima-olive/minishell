#include "../sigma_minishell.h"

char	*quote(char *str)
{
	char	ch;
	int		ind;
	char	*ret;

	str = expand(str);
	ret = str;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			ind = 0;
			ch = str[ind];
			ind++;
			while (str[ind] != ch)
				ind++;
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
			ft_memmove(str, str + 1, ft_strlen(str));
			str += ind - 1;
		}
		else
			str++;
	}
	return (ret);
}

char	*expand(char *str)
{
	int		ind;
	int		count;

	if (str == NULL)
		return (btree()->type = ERROR, NULL);
	ind = 0;
	count = 0;
	while (str[ind])
	{
		if (str[ind] == '\'' && ++ind)
			while (str[ind] != '\'')
				ind++;
		if (str[ind] == '$' && (ft_isalnum(str[ind + 1]) || str[ind + 1] == '?' || str[ind + 1] == '_'))
		{
			count++;
			if (str[ind + 1] == '?')
				return (expand_aux(str, ind, 2, NULL));
			while (ft_isalnum((str + ind)[count]) || (str + ind)[count] == '_')
				count++;
			return (expand_aux(str, ind, count, NULL));
		}
		ind++;
	}
	return (str);
}
