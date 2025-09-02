	#include "../sigma_minishell.h"
	#include <stdlib.h>
	#include <sys/wait.h>
	#include <unistd.h>

	int exec_tree(t_binary *tree)
	{
		int ret_left;
		
		if (!tree)
			return (0);
		if (tree->cmds != NULL)
			return (exec_pipes(tree->cmds, tree->env));
		if (tree->type == AND)
		{
			ret_left = exec_tree(tree->left);
			if (ret_left == 0)
				return (exec_tree(tree->right));
			return (ret_left);
		}
		if (tree->type == OR)
		{
			ret_left = exec_tree(tree->left);
			if (ret_left != 0)
				return (exec_tree(tree->right));
			return (exec_tree(tree->left));
		}
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