#include "../sigma_minishell.h"


int    exec_pipes(t_cmds *cmd, char **env)
{
	int fd[2];
	int first_fd = -1;
	pid_t pid;

	if (!cmd || cmd->cmd[0] == NULL)
		return (0);
	while (cmd)
	{
		if (cmd->next != NULL)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (first_fd != -1)
			{
				dup2(first_fd, STDIN_FILENO);
				close(first_fd);
			}
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (is_builtin(cmd->cmd[0]))
				exec_builtin(cmd->cmd[0], cmd->cmd);
			else
				exec_path(cmd->cmd[0], cmd->cmd, env);
			exit (1);
		}
		if (first_fd != -1)
			close(first_fd);
		if (cmd->next != NULL)
		{
			close(fd[1]);
			first_fd = fd[0];
		}
		cmd = cmd->next;
	}
	int status;
	while (waitpid(-1, &status, WNOHANG) > 0);
	return (WEXITSTATUS(status));
}