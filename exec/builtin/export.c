/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 23:57:32 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:47:38 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

static int	make_update_env_aux(t_os_envs **env_list, const char *str,
		size_t len)
{
	t_os_envs	*current;
	char		*new_var;

	current = *env_list;
	while (current)
	{
		if (current->linux_envs && ft_strncmp(current->linux_envs, str,
				len) == 0 && current->linux_envs[len] == '=')
		{
			new_var = ft_strdup(str);
			if (!new_var)
				return (-1);
			free(current->linux_envs);
			current->linux_envs = new_var;
			return (0);
		}
		current = current->next;
	}
	return (1);
}

static size_t	get_env_key_length(const char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		return ((size_t)(equal_sign - str));
	else
		return (strlen(str));
}

int	add_new_env_var(t_os_envs **env_list, const char *str)
{
	t_os_envs	*new_node;
	t_os_envs	*current;

	new_node = malloc(sizeof(t_os_envs));
	if (!new_node)
		return (-1);
	new_node->linux_envs = ft_strdup(str);
	if (!new_node->linux_envs)
		return (free(new_node), -1);
	new_node->temp_vars = NULL;
	new_node->next = NULL;
	if (!*env_list)
	{
		*env_list = new_node;
	}
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

int	make_update_env(const char *str)
{
	t_os_envs	**env_list;
	size_t		len;
	int			result;

	env_list = get_env_list();
	len = get_env_key_length(str);
	result = make_update_env_aux(env_list, str, len);
	if (result == 0)
		return (0);
	if (result == -1)
		return (-1);
	return (add_new_env_var(env_list, str));
}

int	builtin_export(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		return (print_env_list(), 0);
	while (args[i])
	{
		if (!strchr(args[i], '='))
		{
			add_temp_var(args[i]);
			i++;
			continue ;
		}
		if (make_update_env(args[i]) < 0)
		{
			return (perror("minishell: export"), 0);
		}
		i++;
	}
	return (0);
}
