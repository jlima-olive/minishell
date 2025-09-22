/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:19:21 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 16:47:08 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	if (first_fd != -1)
		dup2(first_fd, STDIN_FILENO);
	if (has_redir(cmd))
		exec_redirections(cmd);
	else if (cmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (first_fd != -1)
		close(first_fd);
}

void	execute_child(t_cmds *cmd, int first_fd, int fd[2], char **env)
{
	char	**cleaned_cmd;
	int		status;

	setup_child_fds(first_fd, fd, cmd);
	cleaned_cmd = array_to_exec(cmd);
	if (is_builtin(cleaned_cmd[0]))
	{
		status = exec_builtin(cleaned_cmd[0], cleaned_cmd, env);
		free_matrix(cleaned_cmd);
		exit(status);
	}
	else
	{
		exec_path(cleaned_cmd[0], cleaned_cmd, env);
		free_matrix(cleaned_cmd);
		exit(1);
	}
}

int	setup_pipe(t_cmds *cmd, int *first_fd, int fd[2])
{
	if (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
	}
	return (0);
}

static int	process_command(t_cmds **cmd, int *first_fd, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (setup_pipe(*cmd, first_fd, fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		execute_child(*cmd, *first_fd, fd, env);
	if (*first_fd != -1)
		close(*first_fd);
	if ((*cmd)->next != NULL)
	{
		close(fd[1]);
		*first_fd = fd[0];
	}
	*cmd = (*cmd)->next;
	return (0);
}

int	exec_pipes(t_cmds *cmd, char **env)
{
	int	first_fd;
	int	status;

	first_fd = -1;
	if (!cmd || cmd->cmd[0] == NULL)
		return (0);
	while (cmd)
	{
		if (process_command(&cmd, &first_fd, env) == -1)
			return (-1);
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
