#include "../sigma_minishell.h"

char	**expand_wildcards(char **mat, int count, char *empty_str, t_wild *head)
{
	char	**pattern;
	char	*limit[2];
	int		ind[2];

	if (btree()->type == ERROR)
		return (NULL);
	pattern = ft_giga_split(mat[count], '*');
	quote_matrix(pattern);
	if (pattern == NULL)
		return (btree()->type = ERROR, NULL);
	if (mat[count][0] == '*')
		limit[0] = empty_str;
	else
		limit[0] = *pattern;
	ind[0] = ft_strlen(mat[count]);
	ind[1] = ft_matlen(pattern);
	if (mat[count][ind[0] - (ind[0] > 0)] == '*')
		limit[1] = empty_str;
	else
		limit[1] = pattern[ind[1] - (ind[1] > 0)];
	head = read_dir("./", NULL, limit[0]);
	head = get_pattern(head, pattern + (*pattern == *limit), limit);
	ft_free_matrix(pattern);
	return (bind_mat_lst(mat, count, head, 0));
}

char	**wildcards_aux(char **mat, int count, int flag)
{
	int 	ind;
	char	ch;
	char	**new;

	ind = 0;
	while (mat[count][ind])
	{
		if ((mat[count][ind] == '\'' || mat[count][ind] == '\"') && ++ind)
		{
			ch = mat[count][ind];
			while (mat[count][ind] != ch)
				ind++;
		}
		if (mat[count][ind] == '*')
		{
			new = expand_wildcards(mat, count, "\0", NULL);
			count += ft_matlen(new) - ft_matlen(mat);
			if (flag && new != mat) //revisit this edgecase
				free(mat);
			return (wildcards(new, count + 1, flag + (new != mat)));
		}
		ind++;
	}
	return (wildcards(mat, count + 1, flag));
}

char	**wildcards(char **mat, int count, int flag)
{
	if (btree()->type == ERROR)
		return (NULL);
	if (mat[count] == NULL)
		return (mat);
	if (ft_strncmp(mat[count], "<<", 3) == 0)
		return (wildcards(mat, count + 2, flag));
	return (wildcards_aux(mat, count, flag));
}
