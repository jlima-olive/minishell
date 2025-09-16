#include "../sigma_minishell.h"

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
	// printf("executing pipes\n");
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
		{
			int status = exec_builtin(cleaned_cmd[0], cleaned_cmd, env);
			free_matrix(cleaned_cmd);
			exit(status);
		}
		else
		{
			exec_path(cleaned_cmd[0], cleaned_cmd, env);
			free_matrix(cleaned_cmd);
			exit(1);
		}
			free_matrix(cleaned_cmd);
			exit(1);
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
    while (wait(&status) > 0);
    return (WEXITSTATUS(status));
}