
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>

t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
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

int main(int ac, char **av, char **envp)
{

	builtin_env();
	while(1)
	{
		char *input = readline("minishell$ ");
		if (!input)
			break;
		add_history(input);
		char **args = ft_split(input, ' ');
		if (!args || !args[0])
		{
			free (input);
			free (args);
			continue;
		}
		btree()->env = envp;
		parsing(input);
			// printf("PODES SO POR TIPO PRINT ERROR POR AGORA\n");
		char *cmd = args[0];  
		if (is_builtin(cmd))  
			exec_builtin(cmd, args);
		else
			exec_path(cmd, args, envp);
		binary_clear(btree());
	}
	return(printf("Closing Minishell\n"), 0);
}