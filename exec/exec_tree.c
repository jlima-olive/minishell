	#include "../sigma_minishell.h"
	#include <stdlib.h>
	#include <sys/wait.h>
	#include <unistd.h>

void	expand_agrs(t_cmds *cmd)
{
	char	**mat;
	char	**temp;
	int		ind;

	temp = cmd->cmd;
	mat = wildcards(temp, 0, 0);
	cmd->expanded = 0;
	if (temp != mat)
	{
		free_matrix_nodes(temp);
		cmd->expanded = 1;
	}
	else
	{
		ind = -1;
		while (mat[++ind])
			mat[ind] = quote(mat[ind]);
	}
	cmd->cmd = mat;
}

static int	exec_single_cmd(t_cmds *cmd)
{
	pid_t	pid;
	int		status;
	char	**cleaned;
	char	**updated_envs;

	if (has_builtin(cmd) && !has_redir(cmd))
	{
		// Builtin without redirections - execute directly
		return (exec_builtin(cmd->cmd[0], cmd->cmd, list_to_char(*get_env_list())));
	}
	else
	{
		// Fork for builtins with redirections or external commands
		pid = fork();
		if (pid == 0)
		{
			if (has_redir(cmd))
				exec_redirections(cmd);
			
			cleaned = array_to_exec(cmd);
			updated_envs = list_to_char(*get_env_list());
			
			if (has_builtin(cmd))
				exit(exec_builtin(cleaned[0], cleaned, updated_envs));
			else
				exec_path(cleaned[0], cleaned, updated_envs);
			
			free_matrix(cleaned);
			free_matrix(updated_envs);
			exit(1);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			signal(SIGINT, handle_sigint);
			return (WEXITSTATUS(status));
		}
	}
}

int	exec_tree(t_binary *tree)
{
	printf("EXECUTING TREE\n");
	int	ret_left;

	if (!tree)
		return (0);
	expand_agrs(tree->cmds);
	// Handle command execution
	if (tree->cmds != NULL)
	{
		if (tree->cmds->next) // Multiple commands means piping
			return (exec_pipes(tree->cmds, btree()->env));
		else // Single command
			return (exec_single_cmd(tree->cmds));
	}
	
	// Handle logical operators
	if (tree->logic && strcmp(tree->logic, "&&") == 0)
	{
		ret_left = exec_tree(tree->left);
		if (ret_left == 0)
			return (exec_tree(tree->right));
		return (ret_left);
	}
	
	if (tree->logic && strcmp(tree->logic, "||") == 0)
	{
		ret_left = exec_tree(tree->left);
		if (ret_left != 0)
			return (exec_tree(tree->right));
		return (ret_left);
	}
	
	// Handle subshell
	if (tree->subshell != NULL)
	{
		pid_t pid = fork();
		if (pid == 0)
			exit(exec_tree(tree->subshell));
		int status;
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	
	return (0);
}