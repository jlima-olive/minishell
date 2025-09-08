
#include "sigma_minishell.h"
#include <unistd.h>

void	print_files(t_infile	*file)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
	while (file)
	{
		printf("red is | file is\n");
		printf("%s	   %s\n", file->token, file->file);
		file = file->next;
	}
} 
=======
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
	static t_binary	tree;

	return (&tree);
}
>>>>>>> cfee328 (pipes working, gotta fix bugs)

void	print_cmds(t_cmds *cmds)
{
	int i = 0;
	while (cmds)
	{
		// printf("===============================================================\n");
		printf("\t\tstarts infile\n");
		print_files(cmds->infiles);
		printf("\t\tend infile\n");
		printf("\t\tstarts commands\n");
		ft_print_matrix(cmds->cmd);
		printf("\t\tend commands\n");
		printf("\t\tstarts outfiles\n");
		print_files((t_infile *)cmds->outfiles);
		printf("\t\tend outfiles\n");
		// printf("===============================================================\n");
		cmds = cmds->next;
	}
}

void	print_tree(t_binary *tree, int sub)
{
	// if (sub)
		// printf("\nentering subshell\n");
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
t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
}

<<<<<<< HEAD
int	main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_cmds	*cmds;
	pid_t	pid;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	builtin_env(envp);
=======
int	main(int ac, char **av, char **envp)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
	char	*input;
	char	**args;
	char	*cmd;

>>>>>>> cfee328 (pipes working, gotta fix bugs)
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
>>>>>>> 6c0dac5 (handle signals complete)
	builtin_env();
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
<<<<<<< HEAD
		if (*input == '\0')
		{
			free(input);
=======
<<<<<<< HEAD
		char **args = ft_split(input, ' ');
=======
		args = ft_split(input, ' ');
>>>>>>> cfee328 (pipes working, gotta fix bugs)
		if (!args || !args[0])
		{
			free(input);
			free(args);
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
			continue ;
		}
		btree()->env = envp;
		parsing(input);
<<<<<<< HEAD
		cmds = btree()->cmds;
		if (!cmds || !cmds->cmd || !cmds->cmd[0])
		{
			free(input);
			binary_clear(btree());
			continue ;
		}
		if (!ft_strchr(input, '|'))
		{
			if (is_builtin(cmds->cmd[0]))
			{
				if (has_redir(cmds))
				{
					pid = fork();
					if (pid == 0)
					{
						exec_redirections(cmds);
						char **cleaned = array_to_exec(cmds);
						exec_builtin(cleaned[0], cleaned, envp);
						free_matrix(cleaned);
						exit(0);
					}
					waitpid(pid, NULL, 0);
				}
				else
					exec_builtin(cmds->cmd[0], cmds->cmd, envp);
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
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
			exec_tree(btree());
		free(input);
=======
<<<<<<< HEAD
<<<<<<< HEAD
			// printf("PODES SO POR TIPO PRINT ERROR POR AGORA\n");
		print_tree(btree(), 0);
=======
>>>>>>> 6c0dac5 (handle signals complete)
		char *cmd = args[0];  
		if (is_builtin(cmd))  
			exec_builtin(cmd, args);
=======
		cmd = args[0];
		if (ft_strchr(input, '|') == NULL) // <-- DEIXAR ESSE IF PQ SE NAO DA MERDA QUANDO NAO EXISTEM PIPES E TENTA EXEC_BUILTIN
		{
		    if (is_builtin(cmd))
		        exec_builtin(cmd, args);
		    else
        		exec_path(cmd, args, envp);
		}
>>>>>>> cfee328 (pipes working, gotta fix bugs)
		else
			exec_tree(btree());
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
		binary_clear(btree());
		free(btree()->mat);
	}
	return (printf("Closing Minishell\n"), 0);
<<<<<<< HEAD
}
=======
}
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
