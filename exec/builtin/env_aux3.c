/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:11:26 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/20 00:11:30 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

size_t	count_env_nodes(t_os_envs *envs)
{
	size_t		count;
	t_os_envs	*temp;

	count = 0;
	temp = envs;
	while (temp)
	{
		if (temp->linux_envs)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	fill_env_array(char **final_char, t_os_envs *envs)
{
	t_os_envs	*temp;
	size_t		i;

	temp = envs;
	i = 0;
	while (temp)
	{
		if (temp->linux_envs)
		{
			final_char[i] = ft_strdup(temp->linux_envs);
			if (!final_char[i])
			{
				free_matrix(final_char);
				free(final_char);
				return (0);
			}
			i++;
		}
		temp = temp->next;
	}
	final_char[i] = NULL;
	return (1);
}

char	**list_to_char(t_os_envs *envs)
{
	size_t	count;
	char	**final_char;
	size_t	i;

	count = count_env_nodes(envs);
	final_char = malloc(sizeof(char *) * (count + 1));
	if (!final_char)
		return (NULL);
	if (!fill_env_array(final_char, envs))
		return (NULL);
	return (final_char);
}

void	add_node_to_list(t_os_envs **env_list, t_os_envs *new_node)
{
	t_os_envs	*last;

	if (*env_list == NULL)
	{
		*env_list = new_node;
	}
	else
	{
		last = *env_list;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

void	rebuild_env_list(t_os_envs **env_list, char **env_vars)
{
	t_os_envs	*new_node;
	t_os_envs	*last;

	while (*env_vars)
	{
		new_node = create_env_node(*env_vars);
		if (!new_node)
		{
			perror("minishell: env");
			return ;
		}
		add_node_to_list(env_list, new_node);
		env_vars++;
	}
}
