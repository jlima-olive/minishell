#include "../sigma_minishell.h"

int	add_env_back(t_os_envs_list **lst, t_os_envs_list *new)
{
	t_os_envs_list	*temp;

	if (lst == NULL || new == NULL)
		return (btree()->type = ERROR, 1) ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

t_os_envs_list	*env_new(char *env)
{
	t_os_envs_list	*new;

	new = malloc(sizeof(t_os_envs_list));
	if (new == NULL)
		return (NULL);
	new->linux_envs = ft_strdup(env);
	new->temp_vars = NULL;
	if (new->linux_envs == NULL)
		return (NULL);
	return (new);
}

void	env_clear(t_os_envs_list *env)
{
	if (env == NULL)
		return ;
	env_clear(env->next);
	free(env->linux_envs);
	free(env->temp_vars);
	free(env);
}

t_os_envs_list	*get_env(char **environ)
{
	t_os_envs_list	*ret;

	ret = NULL;
	while (*environ)
		if (add_env_back(&ret, env_new(*environ)))
			return (env_clear(ret), NULL);
	return (ret);
}
