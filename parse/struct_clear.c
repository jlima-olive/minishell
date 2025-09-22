
#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

void	binary_clear(t_binary *binary)
{
	if (binary == NULL)
		return ;
	binary_clear(binary->left);
	binary_clear(binary->right);
	binary_clear(binary->subshell);
	cmds_clear(binary->cmds);
	free (binary->logic);
	free (binary->print_cmd);
	if (binary->up)
		free(binary);
	else
		free_matrix(binary->mat);
}

void	cmds_clear(t_cmds *cmds)
{
	int	ind;

	if (cmds == NULL)
		return ;
	cmds_clear(cmds->next);
	cmds->next = NULL;
	outfile_clear(cmds->outfiles);
	infile_clear(cmds->infiles);
	ind = -1;
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
	free(infile->file);
	free(infile->token);
	free(infile);
}

void	outfile_clear(t_outfile *outfile)
{
	if (outfile == NULL)
		return ;
	outfile_clear(outfile->next);
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