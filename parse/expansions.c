#include "../sigma_minishell.h"

char	*quote(char *str)
{
	char	ch;
	int		ind;
	char	*ret;

	str = expand(str, 0, 0, 1);
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

char	*find_os_env(t_os_envs *env, char *str, int count)
{
	while (env)
	{
		if (env->linux_envs && ft_strncmp(env->linux_envs, str, count) == 0)
			return (env->linux_envs);
		env = env->next;
	}
	return (NULL);
}

char	*expand_aux(char *str, int ind, int count, char *temp)
{
	char	*env_var;

	temp = ft_strndup(str + ind + 1, count - 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(temp, "=", 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	env_var = find_os_env(btree()->os_env, temp, count);
	// printf( "we found %s\n", env_var);
	free(temp);
	if (env_var == NULL)
		env_var = ft_calloc(1, 1);
	if (env_var == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strdup(str + ind + count);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(env_var + count * (*env_var != '\0'), temp, 2);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	str[ind] = '\0';
	str = ft_strjoin_free(str, temp, 0);
	// str = ft_strjoin(str, temp);
	if (str == NULL)
		return (btree()->type = ERROR, NULL);
	return (expand(str, 0, 0, 1));
}

char    *expand(char *str, int ind, int count, int flag)
{
    if (str == NULL)
        return (btree()->type = ERROR, NULL);
    ind = 0;
    while (str[ind])
    {
        if (flag == 1 && str[ind] == '\'' && ++ind)
            while (str[ind] != '\'')
                ind++;
        if (str[ind] == '\"')
            flag = -flag;
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
