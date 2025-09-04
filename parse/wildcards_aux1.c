#include "../sigma_minishell.h"

void	add_wild_back(t_wild **lst, t_wild *new)
{
	t_wild	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	wildsize(t_wild *head)
{
	int	ind;

	ind = 0;
	while (head)
	{
		head = head->next;
		ind++;
	}
	return (ind);
}

void	quote_matrix(char **mat)
{
	while (mat && *mat)
	{
		*mat = quote(*mat);
		mat++;
	}
}

void	sort_wild(t_wild *wild1)
{
	t_wild *wild2;

	while (wild1)
	{
		wild2 = wild1->next;
		while (wild2)
		{
			if (ft_abs_strcmp(wild1->file, wild2->file) > 0)
				ft_ult_swap(&wild1->file, &wild2->file);
			wild2 = wild2->next;
		}
		wild1 = wild1->next;
	}
}

t_wild	*get_pattern(t_wild *head, char **pattern, char **limit)
{
	t_wild	*temp;
	size_t	len;

	if (limit[0][0])
		remove_non_start(&head, limit[0], ft_strlen(limit[0]));
	if (limit[1][0])
		remove_non_end(&head, limit[1]);
	while (head && pattern && *pattern)
	{
		len = ft_strlen(*pattern);
		temp = head;
		while (temp)
		{
			temp->search = ft_strstr(temp->search, *pattern);
			if (temp->search)
				temp->search += len;
			temp = temp->next;
		}
		pattern++;
		remove_null(&head, NULL, NULL);
	}
	return (head);
}