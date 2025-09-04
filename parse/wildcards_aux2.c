#include "../sigma_minishell.h"

static int	check_end(char *big, char *little)
{
	int	big_len;
	int	little_len;

	big_len = strlen(big);
	little_len = strlen(little);
	if (big_len < little_len)
		return (1);
	big += big_len - little_len;
	return (ft_strcmp(big, little));
}

void	remove_non_end(t_wild **head, char *end)
{
	t_wild *node;
	t_wild *next;

	while (*head && check_end((*head)->file, end))
	{
		node = (*head)->next;
		free ((*head)->file);
		free (*head);
		*head = node;
	}
	if (*head == NULL)
		return ;
	node = *head;
	while (node->next)
	{
		next = node->next;
		if (check_end(next->file, end))
		{
			node->next = next->next;
			free (next->file);
			free (next);
		}
		else
			node = next;
	}
}

void	remove_null(t_wild **head, t_wild *node, t_wild *next)
{
	while ((*head)->search == NULL)
	{
		node = (*head)->next;
		free ((*head)->file);
		free (*head);
		*head = node;
		if (*head == NULL)
			return ;
	}
	node = (*head);
	while (node->next)
	{
		next = node->next;
		if (next->search == NULL)
		{
			node->next = next->next;
			free (next->file);
			free (next);
		}
		else
			node = next;
	}
}

void	remove_non_start(t_wild **head, char *start, int len)
{
	t_wild *node;
	t_wild *next;

	while (*head && ft_strnstr((*head)->file, start, len) == NULL)
	{
		node = (*head)->next;
		free ((*head)->file);
		free (*head);
		*head = node;
	}
	if (*head == NULL)
		return ;
	node = *head;
	while (node->next)
	{
		next = node->next;
		if (ft_strnstr(next->file, start, len) == NULL)
		{
			node->next = next->next;
			free (next->file);
			free (next);
		}
		else
			node = next;
	}
}
