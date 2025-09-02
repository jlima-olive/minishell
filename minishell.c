
#include "sigma_minishell.h"

t_binary	*btree(void)
{
	static t_binary	tree;

	return (&tree);
}

void	print_cmds(t_cmds *cmds)
{
	int i = 0;
	while (cmds)
	{
		printf("===============================================================\n");
		printf("\t\tstarts infile\n");
		print_files(cmds->infiles);
		printf("\t\tend infile\n");
		printf("\t\tstarts commands\n");
		ft_print_matrix(cmds->cmd);
		printf("\t\tend commands\n");
		printf("\t\tstarts outfiles\n");
		print_files((t_infile *)cmds->outfiles);
		printf("\t\tend outfiles\n");
		printf("===============================================================\n");
		cmds = cmds->next;
	}
}

void	print_tree(t_binary *tree, int sub)
{
	if (sub)
		printf("\nentering subshell\n");
	if (tree == NULL)
		return ;
	print_tree(tree->subshell, 1);
	print_tree(tree->left, 0);
	print_tree(tree->right, 0);
	if (tree->left == NULL && tree->right == NULL)
		if (tree->cmds)
			print_cmds(tree->cmds);
	if (sub)
		printf("\n^exiting shubshell^\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmds;
	pid_t	pid;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	builtin_env();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		btree()->env = envp;
		parsing(input); // Fills btree()->cmds
		cmds = btree()->cmds;
		if (!cmds || !cmds->cmd || !cmds->cmd[0])
		{
			free(input);
			binary_clear(btree());
			continue ;
		}
		// print_cmds(cmds);
		if (!ft_strchr(input, '|'))
		{
			if (is_builtin(cmds->cmd[0]))
			{
				// printf("==IS_BUILTIN 1\n");
				if (has_redir(cmds))
				{
					// printf("==HAS_REDIR 1\n");
					pid = fork();
					if (pid == 0)
					{
						exec_redirections(cmds);
						char **cleaned = array_to_exec(cmds);
						exec_builtin(cleaned[0], cleaned);
						free_matrix(cleaned);
						exit(0);
					}
					waitpid(pid, NULL, 0);
				}
				else
					exec_builtin(cmds->cmd[0], cmds->cmd)/* , printf("SOOCBYDOO\n") */;
			}
			else
			{
				// printf("=======NAO E BUILTIN\n");
				pid = fork();
				if (pid == 0)
				{
					// printf("=======PID IGUAL A 0\n");
					if (has_redir(cmds))
						exec_redirections(cmds);
					char **cleaned = array_to_exec(cmds);
        			exec_path(cleaned[0], cleaned, envp);
        			free_matrix(cleaned);
					exit(1);
				}
				waitpid(pid, NULL, 0);
			}
		}
		else
		{
			exec_tree(btree());
		}
		free(input);
		binary_clear(btree());
	}
	return (printf("Closing Minishell\n"), 0);
}
