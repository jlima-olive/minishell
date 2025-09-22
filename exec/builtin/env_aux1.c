/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:59 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/21 15:56:28 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

t_os_envs	**get_env_list(void)
{
	static t_os_envs	*env_list = NULL;

	return (&env_list);
}


t_os_envs	*create_env_node(char *path)
{
	t_os_envs	*new_node;

	new_node = malloc(sizeof(t_os_envs));
	if (!new_node)
		return (NULL);
	new_node->linux_envs = ft_strdup(path);
	if (!new_node->linux_envs)
		return (free(new_node), NULL);
	new_node->next = NULL;
	new_node->temp_vars = NULL;
	return (new_node);
}

void	clear_env_list(void)
{
	t_os_envs	**env_list;
	t_os_envs	*current;
	t_os_envs	*next;

	env_list = get_env_list();
	current = *env_list;
	while (current)
	{
		next = current->next;
		free(current->linux_envs);
		free(current->temp_vars);
		free(current);
		current = next;
	}
	*env_list = NULL;
}

void	enhanced_sort_wild_vini_goat(t_os_envs *envs)
{
	t_os_envs	*env2;

	while (envs)
	{
		env2 = envs->next;
		while (env2)
		{
			if (ft_abs_strcmp(envs->linux_envs, env2->linux_envs) > 0)
				ft_ult_swap(&envs->linux_envs, &env2->linux_envs);
			env2 = env2->next;
		}
		envs = envs->next;
	}
}

void	print_env_list(void)
{
	t_os_envs	*current;

	current = *get_env_list();
	while (current)
	{
		if (current->linux_envs)
			printf("declare -x %s\n", current->linux_envs);
		if (current->temp_vars)
			printf("declare -x %s\n", current->temp_vars);
		current = current->next;
	}
}
