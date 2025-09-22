/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:36:54 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:26:48 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

char	*find_path(char **envp, char *which_env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], which_env, (ft_strlen(which_env))) == 0)
			return (ft_strdup(envp[i] + ft_strlen(which_env)));
		i++;
	}
	return (NULL);
}

char	**split_path(char **envp)
{
	char	*path;
	char	**vars;

	path = find_path(envp, "PATH=");
	if (!path)
		return (NULL);
	vars = ft_split(path, ':');
	free(path);
	return (vars);
}

char	**get_paths_to_search(char **envp)
{
	return (split_path(envp));
}

int	check_path_access(char *path, char *cmd)
{
	int		result;
	char	*full_path;

	full_path = malloc(strlen(path) + strlen(cmd) + 2);
	if (!full_path)
	{
		perror("malloc failed");
		return (-1);
	}
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	result = (access(full_path, X_OK) == 0);
	free(full_path);
	return (result);
}

int	is_system_path_command(char *cmd, char **envp)
{
	int		i;
	int		access_result;
	char	**paths_to_search;

	paths_to_search = get_paths_to_search(envp);
	if (!paths_to_search)
		return (-1);
	i = 0;
	while (paths_to_search[i])
	{
		access_result = check_path_access(paths_to_search[i], cmd);
		if (access_result == -1)
		{
			free_matrix(paths_to_search);
			return (-1);
		}
		if (access_result == 1)
		{
			free_matrix(paths_to_search);
			return (1);
		}
		i++;
	}
	free_matrix(paths_to_search);
	return (0);
}
