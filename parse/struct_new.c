
#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

t_outfile	*outfile_new(char *file, char *token)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	if (new == NULL)
		return (NULL);
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_infile	*infile_new(char *file, char *token)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (new == NULL)
		return (NULL);
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_cmds	*cmds_new(t_outfile *outfile, t_infile *infile, char **cmd)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	new->cmd = cmd;
	new->outfiles = outfile;
	new->infiles = infile;
	new->next = NULL;
	return (new);
}

t_binary	*binary_new(int shlvl, t_type type, t_binary *up, t_cmds *cmds)
{
	t_binary	*new;

	new = malloc(sizeof(t_binary));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->sublvl = shlvl;
	new->left_ret = -1;
	new->right_ret = -1;
	new->subshell_ret = -1;
	new->cmds = cmds;
	new->up = up;
	new->left = NULL;
	new->right = NULL;
	new->subshell = NULL;
	new->mat = NULL;
	return (new);
}

t_wild	*wild_new(char *file, char d_type)
{
	t_wild	*new;

	if (file == NULL)
		return (btree()->type = ERROR, NULL);
	new = malloc(sizeof(t_wild));
	if (new == NULL)
		return (btree()->type = ERROR, NULL);
	new->file = file;
	new->search = file;
	new->d_type = d_type;
	new->next = NULL;
	return (new);
}
