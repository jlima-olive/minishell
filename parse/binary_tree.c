
#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

/* 
int	output_comp(char *str)
{
	if (strncmp(str, ">>", 3) == 0 || strncmp(str, "&>", 3) == 0\
		|| strncmp(str, "0>", 3) == 0 || strncmp(str, "1>", 3) == 0\
			|| strncmp(str, "2>", 3) == 0 || strncmp(str, ">&", 3) == 0)
					return (0);
	if (strncmp(str, "0<>", 4) == 0 || strncmp(str, "1<>", 4) == 0 \
		|| strncmp(str, "&>>", 4) == 0 || strncmp(str, "0>>", 4) == 0\
			|| strncmp(str, "1>>", 4) == 0 || strncmp(str, "2>>", 4) == 0\
				|| strncmp(str, "2<>", 4) == 0)\
						return (0);
	return (1);
}

int	input_comp(char *str)
{
	if (strncmp(str, "<<", 3) && strncmp(str, "<>", 3) && strncmp(str, "<", 2))
		return (1);
	return (0);
}
*/


/*
int redirect_comp(char *str)
{
	if (strncmp(str, "0>&1", 5) == 0 || strncmp(str, "1>&0", 5) == 0\
		|| strncmp(str, "2>&0", 5) == 0 || strncmp(str, "1>&2", 5) == 0\
			|| strncmp(str, "2>&1", 5) == 0 || strncmp(str, "0>&2", 5) == 0)
					return (0);
	return (1);
}

 output is:
	">>", "&>", ">&", "0>", "1>", "2>"
	"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
	"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

input is:
	"<<", "<", "<>"
*/
int	separator_comp(char **mat, int flag)
{
	int	ind;
	int	pcount;

	ind = ft_matlen(mat) - 1;
	pcount = 0;
	if (flag == 1)
	{
		while (ind >= 0)
		{
			if (ft_strncmp(mat[ind], ")", 2) == 0)
			{
				pcount++;
				ind--;
				while (ind >= 0 && pcount)
				{
					if (ft_strncmp(mat[ind], ")", 2) == 0)
						pcount++;
					if (ft_strncmp(mat[ind], "(", 2) == 0)
						pcount--;
					ind--;
				}
			}
			if (ind >= 0 && (ft_strncmp(mat[ind], "&&", 3) == 0 || ft_strncmp(mat[ind], "||", 3) == 0))
				return (ind);
			ind--;
		}
	}
	else
	{
		while (ind-- > 0)
			if (ft_strncmp(mat[ind], "&", 2) == 0)
				return (ind);
	}
	return (0);
} 

int	input_comp(char *str)
{
	if (strncmp(str, "<<", 3) && strncmp(str, "<", 2))
		return (1);
	return (0);
}

int	output_comp(char *str)
{
	if (strncmp(str, ">>", 3) && strncmp(str, ">", 2))
		return (1);
	return (0);
}

t_infile	*get_infile(char **mat)
{
	t_infile	*infile;
	int			ind;

	if (mat == NULL || *mat == NULL)
		return (NULL);
	ind = 0;
	while (mat[ind] && input_comp(mat[ind]))
		ind++;
	if (mat[ind] == NULL)
		return (NULL);
	infile = infile_new(mat[ind + 1], mat[ind]);
	if (infile == NULL)
		return (NULL);
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

	if (mat == NULL || *mat == NULL)
		return (NULL);
	ind = 0;
	// test if we really need ft_strncmp(mat[ind], "|", 2), I dont think we do
	while (mat[ind] && ft_strncmp(mat[ind], "|", 2) && output_comp(mat[ind]))
		ind++;
	if (mat[ind] == NULL || ft_strncmp(mat[ind], "|", 2) == 0)
		return (NULL);
	outfile = outfile_new(mat[ind + 1], mat[ind]);
	if (outfile == NULL)
		return (NULL);
	mat[ind] = NULL;
	mat[ind + 1] = NULL;
	ft_matrix_uni(mat + ind, mat + ind + 2);
	outfile->next = get_outfile (mat + ind);
	return (outfile);
}

int	find_pipe(char **mat)
{
	int ind;

	ind = 0;
	while (mat[ind] && ft_strncmp(mat[ind], "|", 2))
		ind++;
	return ((mat[ind] == NULL) * -1 + (mat[ind] != NULL) * ind);
}

void	print_files(t_infile	*file)
{
	while (file)
	{
		printf("red is | file is\n");
		printf("%s       %s\n", file->token, file->file);
		file = file->next;
	}
}

t_cmds	*get_cmds(char **mat)
{
	t_cmds	*cmds;
	int		sep;

	if (mat == NULL || *mat == NULL)
		return (NULL);
	sep = find_pipe(mat);
	if (sep != -1)
	{
		free(mat[sep]);
		mat[sep] = NULL;
	}
	cmds = cmds_new(get_outfile(mat), get_infile(mat), mat);
	if (sep != -1)
		cmds->next = get_cmds(mat + sep + 1);
	return (cmds);
}

// in < cat | cat & echo done & echo ola
// in < cat | cat & echo done &


void	create_binary_tree(char **mat, int	shlvl, t_binary *tree)
{
	int	sub;

	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return ;
	sub = separator_comp(mat, 0);
	if (sub)
	{
		free(mat[sub]);
		mat[sub] = NULL;
		tree->subshell = binary_new(shlvl - 1, EMPTY, tree, NULL);
		if (tree->subshell == NULL)
		{
			btree()->type = ERROR;
			return ;
		}
		create_binary_tree (mat, shlvl - 1, tree->subshell);
		if (btree()->type == ERROR)
			return ;
		mat += sub + 1;
	}
	// ft_print_matrix(mat);
	// printf("^===============================================================^\n");
	create_binary_lvl(mat, shlvl, tree);
}

int	open_parethesis(char **mat)
{
	int	ind;
	int	pcount;

	ind = 0;
	pcount = 0;
	if (ft_strncmp(mat[ind], "(", 2) == 0)
	{
		pcount++;
		while (pcount && mat[++ind])
		{
			if (ft_strncmp(mat[ind], "(", 2) == 0)
				pcount++;
			if (ft_strncmp(mat[ind], ")", 2) == 0)
				pcount--;
		}
		if (pcount == 0 && mat[ind + 1] == NULL)
		{
			free (*mat);
			free (mat[ind]);
			*mat = NULL;
			mat[ind] = NULL;
			return (1);
		}
	}
	return (0);
}

void    print_thiscmds(t_cmds *cmds)
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
// 
// int	check_syntax(char **mat)
// {
	// if ()
	// return (0);
// }

void	create_binary_lvl(char **mat, int id, t_binary *tree)
{
	int			sep;

	if (mat == NULL || *mat == NULL)
	{
		if (tree->up != NULL)
			free(tree);
		return ;
	}
	mat += open_parethesis(mat);
	// if (check_syntax(mat))
		// btree()->type = ERROR;
	if (btree()->type == ERROR)
		return ;
	sep = separator_comp(mat, 1);
	if (sep == 0)
	{
		tree->table = table_new(get_infile(mat), get_cmds(mat));
		return ;
	}
	tree->left = binary_new(id ,EMPTY, tree, NULL);
	if (tree->left == NULL)
	{
		btree()->type = ERROR;
		return ;
	}
	tree->right = binary_new(id ,EMPTY, tree, NULL);
	if (tree->right == NULL)
	{
		btree()->type = ERROR;
		return ;
	}
	if (ft_strncmp(mat[sep], "&&", 3) == 0)
		tree->type = AND;
	else
		tree->type = OR;
	free (mat[sep]);
	mat[sep] = NULL;
	// printf("===============================================================\n");
	// ft_print_matrix(mat);
	create_binary_lvl (mat, 1, tree->left);
	// print_files(get_infile(mat));
	// // print_thiscmds(get_cmds(mat));
	// // printf("^left===============================================================^\n");
	// ft_print_matrix(mat);
	create_binary_lvl (mat + sep + 1, 1, tree->right);
	// print_files(get_infile(mat + sep + 1));	
	// print_thiscmds(get_cmds(mat + sep + 1));
	// ft_print_matrix(mat + sep + 1);
	// printf("^right==============================================================^\n");
}
