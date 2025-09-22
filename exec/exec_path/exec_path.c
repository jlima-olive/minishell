/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:44:52 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:27:03 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

int	handle_env_var_cmd(char *cmd, char **args, char **envp)
{
	char	*value;

	if (cmd[0] == '$')
	{
		value = get_env_var(cmd + 1, envp);
		if (strchr(value, '/'))
		{
			prepare_for_exec();
			execve(value, args, envp);
			my_ffprintf(cmd, "No such file or directory\n");
			return (-1);
		}
		else
		{
			prepare_for_exec();
			execve(value, args, envp);
			my_ffprintf(cmd, "command not found\n");
			return (-1);
		}
	}
	return (0);
}

int	handle_absolute_path_cmd(char *cmd, char **args, char **envp)
{
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				prepare_for_exec();
				execve(cmd, args, envp);
				perror(cmd);
				return (-1);
			}
		}
	}
	return (0);
}

int	handle_system_path_cmd_aux(char *cmd, char **args, char **envp)
{
	char	*new_args[3];

	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			prepare_for_exec();
			execve(cmd, args, envp);
			if (errno == ENOEXEC)
			{
				new_args[0] = "/bin/bash";
				new_args[1] = cmd;
				new_args[2] = NULL;
				prepare_for_exec();
				execve(new_args[0], new_args, envp);
			}
			return (perror(cmd), -1);
		}
		else
			return (perror("minishell"), -1);
	}
	return (0);
}

int	handle_system_path_cmd(char *cmd, char **args, char **envp)
{
	if (is_system_path_command(cmd, envp))
	{
		if (exec_system_path(cmd, args, envp) == 0)
			return (0);
	}
	else
	{
		if (handle_system_path_cmd_aux(cmd, args, envp) != 0)
			return (-1);
	}
	return (0);
}

int	exec_path(char *cmd, char **args, char **envp)
{
	if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd,
			X_OK) == 0)
		update_shell_level(1);
	if (handle_env_var_cmd(cmd, args, envp) != 0)
		return (-1);
	if (handle_absolute_path_cmd(cmd, args, envp) != 0)
		return (-1);
	if (handle_system_path_cmd(cmd, args, envp) != 0)
		return (-1);
	printf("command not found\n");
	return (-1);
}
