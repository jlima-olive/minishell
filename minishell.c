
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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
}  

t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
}
int main(int argc, char *argv[], char **envp)
{
	// struct termios old_term;
    char    *input;
    t_cmds  *cmds;
    pid_t   pid;
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &btree()->orig_termios);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    builtin_env(envp);
	if (am_i_truly_myself(argv[0]))
        update_shell_level(1);
    // now regenerate envp for child processes
    btree()->env = list_to_char(*get_env_list());
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
            cmds = btree()->cmds;
            // print_cmds(cmds);
            // print_tree(btree(), 0);
            if (!btree()->cmds || !btree()->cmds->cmd || !btree()->cmds->cmd[0])
            {
                if (btree()->cmds && btree()->cmds->infiles)
                    discard_heredoc(btree()->cmds->infiles);
                // printf("getting rid of tree\n"); // found you bitch
                if (exec_tree(btree()) == 0){
                    free(input);
                    binary_clear(btree());
                    continue;
                }
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
                        else
                        {
                            signal(SIGINT, SIG_IGN);          // parent ignores SIGINT
                            waitpid(pid, NULL, 0);
                            signal(SIGINT, handle_sigint);    // restore handler
                        }
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
						char **updated_envs = list_to_char(*get_env_list());
                        exec_path(cleaned[0], cleaned, updated_envs);
                        free_matrix(cleaned);
						free_matrix(updated_envs);
                        exit(1);
                    }
                    else
                    {
                        signal(SIGINT, SIG_IGN);          // parent ignores SIGINT
                        waitpid(pid, NULL, 0);
                        signal(SIGINT, handle_sigint);    // restore handler
                    }
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

