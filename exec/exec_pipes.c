#include "../sigma_minishell.h"

<<<<<<< HEAD
int count_cmds(t_cmds *cmd)
{
	size_t i = 0;
	if (!cmd)
		return (0);
	i++;
	while (cmd->next != NULL)
	{
		i++;
		cmd = cmd->next;
	}	
	return (i);
}

int exec_pipes(t_cmds *cmd, char **env)
{
    int fd[2];
    int first_fd = -1;
    pid_t pid;

    if (!cmd || cmd->cmd[0] == NULL)
        return (0);
=======

int    exec_pipes(t_cmds *cmd, char **env)
{
	int fd[2];
	int first_fd = -1;
	pid_t pid;

	if (!cmd || cmd->cmd[0] == NULL)
		return (0);
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
	while (cmd)
	{
		if (cmd->next != NULL)
			pipe(fd);
<<<<<<< HEAD

=======
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
		pid = fork();
		if (pid == 0)
		{
			if (first_fd != -1)
<<<<<<< HEAD
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
			char **cleaned_cmd = array_to_exec(cmd);
			if (is_builtin(cleaned_cmd[0]))
				exec_builtin(cleaned_cmd[0], cleaned_cmd, env);
			else
				exec_path(cleaned_cmd[0], cleaned_cmd, env);
			free_matrix(cleaned_cmd);
			exit(1);
=======
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
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
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
<<<<<<< HEAD

    int status;
    while (wait(&status) > 0);
    return (WEXITSTATUS(status));
=======
	int status;
	while (waitpid(-1, &status, WNOHANG) > 0);
	return (WEXITSTATUS(status));
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
}