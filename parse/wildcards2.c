#include "../sigma_minishell.h"

char	**bind_mat_lst_aux(char **mat, char **ret, int count, t_wild *head)
{
	int	ind;

	ind = 0;
	while (ind < count)
	{
		ret[ind] = mat[ind];
		printf("ret[%d] = %s\n", ind, mat[ind]);
		fflush(stdout);
		ind++;
	}
	while (head)
	{
		ret[ind] = ft_strdup(head->file);
		printf("ret[%d] = %s\n", ind, head->file);
		fflush(stdout);
		head = head->next;
		ind++;
	}
	while (mat[++count])
	{
		ret[ind] = mat[count];
		printf("ret[%d] = %s\n", ind, mat[count]);
		fflush(stdout);
		ind++;
	}
	printf("ret[%d] = %s\n", ind, ret[ind]);
	fflush(stdout);
	return (ret);
}

char	**bind_mat_lst(char **mat, int count, t_wild *head, int ind)
{
	char	**ret;

	if (head == NULL)
		return (mat);
	ind = ft_matlen(mat) + wildsize(head) - 1;
	// printf("printing mat\n");
	// ft_print_matrix(mat);
	// printf("printing head\n");
	// print_wild(head);
	// printf("done printing\n\n");
	// printf("safe\n");
	ret = malloc(sizeof(char *) * (ind + 1));
	if (ret == NULL)
		return (btree()->type = ERROR, NULL);
	// printf("%d\n", ind);
	ret[ind] = NULL;
	sort_wild(head);
	ret = bind_mat_lst_aux(mat, ret, count, head);
	wild_clear(head);
	return (ret);
}

int	hidden_files(char *file, char *start)
{
	if (*file != '.' && *start != '.')
		return (1);
	if (*file == '.' && *start == '.')
		return (1);
	return (0);
}

t_wild	*read_dir(char *dir, t_wild *head, char *start)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*str;

	directory = opendir(dir);
	if (directory == NULL)
		return (btree()->type = ERROR, NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (hidden_files(entry->d_name, start))
		{
			str = ft_strdup(entry->d_name);
			add_wild_back(&head, wild_new(str, entry->d_type));
		}
		if (btree()->type == ERROR)
			return (wild_clear(head), closedir(directory), NULL);
		entry = readdir(directory);
	}
	closedir(directory);
	return (head);
}
