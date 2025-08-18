
#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

t_outfile	*outfile_new(char *file, char *token)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_infile	*infile_new(char *file, char *token)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_cmds	*cmds_new(t_outfile *outfile, char **cmd)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	new->cmd = cmd;
	new->outfiles = outfile;
	new->next = NULL;
	return (new);
}

t_table	*table_new(t_infile *infile, t_cmds *cmds)
{
	t_table	*new;

	new = malloc(sizeof(t_table));
	new->cmds = cmds;
	new->infiles = infile;
	return (new);
}

t_binary	*binary_new(int shlvl, t_type type, t_binary *up, t_table *table)
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
	new->table = table;
	new->up = up;
	new->left = NULL;
	new->right = NULL;
	new->subshell = NULL;
	new->mat = NULL;
	return (new);
}
