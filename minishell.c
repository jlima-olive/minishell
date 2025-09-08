
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>
/* 
void	print_files(t_infile	*file)
{
	while (file)
	{
		printf("red is | file is\n");
		printf("%s	   %s\n", file->token, file->file);
		file = file->next;
	}
} 

void	print_cmds(t_cmds *cmds)
{
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
}  */

t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_cmds	*cmds;
	pid_t	pid;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	builtin_env(envp);
	btree()->env = envp;
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
		// print_cmds(cmds);
		if (parsing(input) == 0)
		{
			cmds = btree()->cmds;
			if (!btree()->cmds || !btree()->cmds->cmd || !btree()->cmds->cmd[0])
			{
				if (btree()->cmds && btree()->cmds->infiles)
					discard_heredoc(btree()->cmds->infiles); // just read & discard <<

				free(input);
				binary_clear(btree());
				continue;
			}
			if (!ft_strchr(input, '|'))
			{
				if (is_builtin(btree()->cmds->cmd[0]))
				{
					if (has_redir(btree()->cmds))
					{
						pid = fork();
						if (pid == 0)
						{
							exec_redirections(btree()->cmds);
							char **cleaned = array_to_exec(btree()->cmds);
							exec_builtin(cleaned[0], cleaned, envp);
							free_matrix(cleaned);
							exit(0);
						}
						waitpid(pid, NULL, 0);
					}
					else
						exec_builtin(btree()->cmds->cmd[0], btree()->cmds->cmd, envp);
				}
				else
				{
					pid = fork();
					if (pid == 0)
					{
						if (has_redir(btree()->cmds))
							exec_redirections(btree()->cmds);
						char **cleaned = array_to_exec(btree()->cmds);
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
			binary_clear(btree());
		}
	}
	return (printf("Closing Minishell\n"), 0);
}
