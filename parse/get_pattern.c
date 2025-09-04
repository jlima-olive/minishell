#include "../sigma_minishell.h"

int	find_pipe(char **mat)
{
	int ind;

	ind = 0;
	while (mat[ind] && ft_strncmp(mat[ind], "|", 2))
		ind++;
	return ((mat[ind] == NULL) * -1 + (mat[ind] != NULL) * ind);
}

static int	input_comp(char *str)
{
	if (strncmp(str, "<<", 3) && strncmp(str, "<", 2))
		return (1);
	return (0);
}

static int	output_comp(char *str)
{
	if (strncmp(str, ">>", 3) && strncmp(str, ">", 2))
		return (1);
	return (0);
}

t_infile	*get_infile(char **mat)
{
	t_infile	*infile;
	int			ind;

	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return (NULL);
	ind = 0;
	while (mat[ind] && input_comp(mat[ind]))
		ind++;
	if (mat[ind] == NULL)
		return (NULL);
	infile = infile_new(mat[ind + 1], mat[ind]);
	if (infile == NULL)
	{
		btree()->type = ERROR;
		return (NULL);
	}
	mat[ind] = NULL;
	mat[ind + 1] = NULL;
	ft_matrix_uni(mat + ind, mat + ind + 2);
	infile->next = get_infile (mat + ind);
	return (infile);
}

t_outfile	*get_outfile(char **mat)
{
	t_outfile	*outfile;
	int			ind;

	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return (NULL);
	ind = 0;
	// test if we really need ft_strncmp(mat[ind], "|", 2), I dont think we do
	while (mat[ind] && ft_strncmp(mat[ind], "|", 2) && output_comp(mat[ind]))
		ind++;
	if (mat[ind] == NULL || ft_strncmp(mat[ind], "|", 2) == 0)
		return (NULL);
	outfile = outfile_new(mat[ind + 1], mat[ind]);
	if (outfile == NULL)
	{
		btree()->type = ERROR;
		return (NULL);
	}
	mat[ind] = NULL;
	mat[ind + 1] = NULL;
	ft_matrix_uni(mat + ind, mat + ind + 2);
	outfile->next = get_outfile (mat + ind);
	return (outfile);
}