#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

void	binary_clear(t_binary *binary)
{
	if (binary == NULL)
		return ;
	// printf("im deleting this\n");
	// fflush(stdout);
	binary_clear(binary->left);
	binary_clear(binary->right);
	binary_clear(binary->subshell);
	cmds_clear(binary->cmds);
	// printf("deleting %s\n", binary->logic);
	// fflush(stdout);
	free (binary->logic);
	// printf("deleting print_cmd'%s'\n", binary->print_cmd);
	// fflush(stdout);
	free (binary->print_cmd);
	if (binary->up)
		free(binary);
	// else
		// env_clear(binary->nv)
	// printf("very much deleted that\n");
	// fflush(stdout);
}

void	cmds_clear(t_cmds *cmds)
{
	if (cmds == NULL)
		return ;
	cmds_clear(cmds->next);
	cmds->next = NULL;
	outfile_clear(cmds->outfiles);
	infile_clear(cmds->infiles);
	// printf("deleting ->");
	// fflush(stdout);
	// ft_print_matrix(cmds->cmd);
	if (cmds->expanded)
		free_matrix (cmds->cmd);
	else
		free_matrix_nodes(cmds->cmd);
	free(cmds);
}

void	infile_clear(t_infile *infile)
{
	if (infile == NULL)
		return ;
	infile_clear(infile->next);
	// printf("%s %s\n", infile->token, infile->file);
	// fflush(stdout);
	free(infile->file);
	free(infile->token);
	free(infile);
}

void	outfile_clear(t_outfile *outfile)
{
	if (outfile == NULL)
		return ;
	outfile_clear(outfile->next);
	// printf("%s %s\n", outfile->token, outfile->file);
	// fflush(stdout);
	free(outfile->file);
	free(outfile->token);
	free(outfile);
}

void	wild_clear(t_wild *node)
{
	if (node == NULL)
		return ;
	wild_clear(node->next);
	free(node->file);
	free(node);
}