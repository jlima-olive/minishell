/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:11:32 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/20 00:11:35 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

void	builtin_env(char **env)
{
	extern char	**environ;
	t_os_envs	**env_list;

	env_list = get_env_list();
	clear_env_list();
	rebuild_env_list(env_list, environ);
	initialize_pwd(env);
}

char	*find_path_in_list(t_os_envs *env_list, const char *key)
{
	size_t	key_len;

	key_len = strlen(key);
	while (env_list)
	{
		if (strncmp(env_list->linux_envs, key, key_len) == 0)
			return (env_list->linux_envs + key_len);
		env_list = env_list->next;
	}
	return (NULL);
}

int	temp_var_exists(t_os_envs *env_list, const char *str)
{
	t_os_envs	*current;

	current = env_list;
	while (current)
	{
		if (current->temp_vars && strcmp(current->temp_vars, str) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	add_new_temp_var(t_os_envs **env_list, const char *str)
{
	t_os_envs	*new_node;
	t_os_envs	*current;

	new_node = malloc(sizeof(t_os_envs));
	if (!new_node)
		return (-1);
	new_node->linux_envs = NULL;
	new_node->temp_vars = ft_strdup(str);
	if (!new_node->temp_vars)
	{
		free(new_node);
		return (-1);
	}
	new_node->next = NULL;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

int	add_temp_var(const char *str)
{
	t_os_envs	**env_list;
	t_os_envs	*current;

	env_list = get_env_list();
	if (temp_var_exists(*env_list, str))
		return (0);
	return (add_new_temp_var(env_list, str));
}
