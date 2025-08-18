
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
		// printf("===============================================================\n");
		printf("starts commands\n\n");
		ft_print_matrix(cmds->cmd);
		printf("end commands\n\n");
		printf("starts outfiles\n\n");
		print_files((t_infile *)cmds->outfiles);
		printf("end outfiles\n");
		// printf("===============================================================\n\n");
		cmds = cmds->next;
	}
}


void	print_tree(t_binary *tree, int sub)
{
	if (tree == NULL)
		return ;
	print_tree(tree->subshell, 1);
	print_tree(tree->left, 0);
	print_tree(tree->right, 0);
	if (tree->left == NULL && tree->right == NULL)
	{
		printf("BEGGINNING table here\n");
		if (tree->table && tree->table->infiles)
		{
			printf("start infiles\n");
			print_files(tree->table->infiles);
			printf("end infiles\n");
		}
		else
		{
			if (tree->up != NULL)
			{
				
			}
			return ;
		}
		if (tree->up == NULL)
			printf("estamos na head?\n");
		if (tree->table && tree->table->infiles)
		{
			printf("table here\n");
			printf("start cmds\n");
			print_cmds(tree->table->cmds);
			printf("end cmds\n");
		}
		printf("ENDING THE table here\n");
	}
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
		// print_tree(btree(), 0);
		// binary_clear(btree());
			// printf("PODES SO POR TIPO PRINT ERROR POR AGORA\n");
		char *cmd = args[0];  
		if (is_builtin(cmd))  
			exec_builtin(cmd, args);
		else
			exec_path(cmd, args, envp);
	}
	return(printf("Closing Minishell\n"), 0);
}