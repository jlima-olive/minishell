
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void	print_files(t_infile	*file)
{
	while (file)
	{
		printf( "red is | file is\n");
		printf( "%s	   %s\n", file->token, file->file);
		file = file->next;
	}
} 

void	print_cmds(t_cmds *cmds)
{
	while (cmds)
	{
		printf( "===============================================================\n");
		printf( "\t\tstarts infile\n");
		print_files(cmds->infiles);
		printf( "\t\tend infile\n");
		printf( "\t\tstarts commands\n");
		ft_print_matrix(cmds->cmd);
		printf( "\t\tend commands\n");
		printf( "\t\tstarts outfiles\n");
		print_files((t_infile *)cmds->outfiles);
		printf( "\t\tend outfiles\n");
		printf( "===============================================================\n");
		cmds = cmds->next;
	}
}

void	print_tree(t_binary *tree, int sub)
{
	// if (sub)
		// printf( "\nentering subshell\n");
	if (tree == NULL)
		return ;
	print_tree(tree->subshell, 1);
	print_tree(tree->left, 0);
	print_tree(tree->right, 0);
	if (tree->left == NULL && tree->right == NULL)
		if (tree->cmds)
			print_cmds(tree->cmds);
	if (sub)
		printf( "\n^exiting shubshell^\n");
}  

t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
}

int main(int argc, char *argv[], char **envp)
{
	char	*input;
	
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &btree()->orig_termios);
	
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	builtin_env(envp);
	
	if (am_i_truly_myself(argv[0]))
		update_shell_level(1);
	
	btree()->env = list_to_char(*get_env_list());
	btree()->os_env = *get_env_list();
	enhanced_sort_wild_vini_goat(btree()->os_env);
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
		
		if (parsing(input) == 0)
		{
			// ALL commands now go through exec_tree
			int exit_status = exec_tree(btree());
			
			// Set last exit status if needed
			// set_exit_status(exit_status);
			
			free(input);
			binary_clear(btree());
		}
	}
	
	return (printf( "Closing Minishell\n"), 0);
}