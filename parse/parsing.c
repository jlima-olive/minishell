#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

/* int	find_fd_red(char *str)
char **tokenization(char *str)
{
	int	ind;

	ind = 0;
	while(str[ind] >= '0' && str[ind] <= '9')
		ind++;
	if (str[ind] == '\0')
		return (0);
	if (str[ind] == '&')
	{
		
		ind++;
	}
	if (str[ind] == '>' && str[ind + 1] == '>')
		return (ind + 2);
	if (str[ind] == '>')
		return (ind + 1);
	return (0);
} */

int	find_tokens(char *str, t_token tokens)
{
	// if (ft_matnstr(tokens.qtokens, str, 4))
		// return (4);
	// if (ft_matnstr(tokens.ttokens, str, 3))
		// return (3);
	if (ft_matnstr(tokens.dtokens, str, 2))
		return (2);
	if (ft_matnstr(tokens.stokens, str, 1))
		return (1);
	return (0);
}

int	word_count(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		count;
	int		token_found;
	char	*sep_found;

	ind = 0;
	count = 0;
	while (str[ind])
	{
		while (str[ind] == ' ' || str[ind] == '\t' || str[ind] == '\n')
			ind++;
		if (str[ind] == '\0')
			return (count);
		token_found = find_tokens(str + ind, tokens);
		if (token_found)
		{
			// write(1, str + ind, token_found);
			// write(1, "\n", 1);
			count++;
			ind += token_found;
		}
		else if (find_tokens(str + ind, tokens) == 0 \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			count++;
			while (find_tokens(str + ind, tokens) == 0 \
				&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
			{
				sep_found = ft_matnstr(sep, str + ind, 1);
				if (sep_found)
				{
					// write(1, str + ind, 1);
					ind++;
					while (str[ind] != *sep_found && str[ind])
					{
						// write(1, str + ind, 1);
						ind++;
					}
					if (str[ind] == '\0')
						return (-(*sep_found));
					// write(1, str + ind, 1);
					ind++;
				}
				else
				{
					// write(1, str + ind, 1);
					ind++;
				}
			}
			// write(1, "\n", 1);
		}
	}
	return (count);
}

static int	parsing_strlen(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		token_found;
	char	*sep_found;

	ind  = 0;
	token_found = find_tokens(str + ind, tokens);
	if (token_found)
		return (token_found);
	else if (find_tokens(str + ind, tokens) == 0 \
		&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		while (find_tokens(str + ind, tokens) == 0 \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			sep_found = ft_matnstr(sep, str + ind, 1);
			if (sep_found)
			{
				ind++;
				while (str[ind] != *sep_found && str[ind])
					ind++;
				if (str[ind] == '\0')
					return (-(*sep_found));
				ind++;
			}
			else
				ind++;
		}
		return (ind);
	}
	return (0);
}

char **tokenization(char *str, t_token tokens, char **sep)
{
	int		wc;
	int		ind;
	int		strcount;
	char	**ret;

	if (str == NULL || *str == '\0')
		return (NULL);
	wc = word_count(str, tokens, sep);
	if (wc < 0)
		return (printf("\nUnclosed |%c|\n", -wc), NULL);
	// printf("\nwords in the input ->|%d|\n", wc);
	ret = malloc(sizeof(char *) * (wc + 1));
	if (ret == NULL)
		return (NULL); // CLOSE PROGRAM INSTEAD OF RETURN NULL WHEN WE FIND MEMORY ERRORS?
	ret[wc] = NULL;
	ind = -1;
	while (++ind < wc)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str == '\0')
			break ;
		strcount = parsing_strlen(str, tokens, sep);
		ret[ind] = ft_strndup(str, strcount);
		if (ret[ind] == NULL)
			return (ft_free_matrix(ret), NULL); // CLOSE PROGRAM INSTEAD OF RETURN NULL WHEN WE FIND MEMORY ERRORS?
		str += strcount;
	}
	// printf("========================================================\n");
	// ft_print_matrix(ret);
	// printf("========================================================\n");
 	return (ret);
}

void init_tree(char	**mat)
{
	btree()->sublvl = 0;
	btree()->type = EMPTY;
	btree()->left_ret = -1;
	btree()->right_ret = -1;
	btree()->subshell_ret = -1;
	btree()->cmds = NULL;
	btree()->up = NULL;
	btree()->left = NULL;
	btree()->right = NULL;
	btree()->subshell = NULL;
	btree()->mat = mat;
}

// output is:
// 	">>", "&>", ">&", "0>", "1>", "2>"
//	"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
//	"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

// input is:
// 	"<<", "<", "<>" 



int	find_syntax(char *str, t_token tokens)
{
	if (ft_matnstr(tokens.dtokens, str, 2))
		return (2);
	if (ft_matnstr(tokens.stokens, str, 1))
		return (1);
	return (0);
}


/* int	check_syntax(char **mat, t_token tokens)
{
	int		ind;
	char	*token_found;
	char	*str;
	char	*stokens[] = {"&", "|", NULL};
	char	*dtokens[] = {"||", "&&", ">>", NULL};

	ind = 0;
	token_found = find_tokens(mat + ind, tokens);
	
} */

int	separator_count(char **mat)
{
	int	count;

	count = 0;
	while (*mat)
	{
		if (strncmp(*mat, "&", 2))
			count++;
		mat++;
	}
	return (count);
}
/* 
char	*dtokens[] = {"<>", "||", "&&", ">>", "<<", "&>", ">&", "0>", "1>", "2>", NULL};
char	*ttokens[] = {"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>", NULL};
char	*qtokens[] = {"0>&1", "1>&0", / ignore left? /"0>&2", "2>&0", "1>&2", "2>&1", NULL};
tokens.ttokens = ttokens;
tokens.qtokens = qtokens;
 if (check_syntax(mat, tokens))
	 printf("wrongggggggg\n");
 else 
	 printf("rightttttttttt\n");
	 return (ft_free_matrix(mat), 1);
 */

int	sep_count(char **mat)
{
	int	count;

	count = 0;
	while (*mat)
	{
		if (ft_strncmp(*mat, "&", 2) == 0)
			count++;
		mat++;
	}
	return (count);
}

char	*expand_aux(char *str, int ind, int count, char *temp)
{
	char	*env_var;

	temp = ft_strndup(str + ind + 1, count - 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(temp, "=", 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	env_var = ft_matnstr(btree()->env, temp, count);
	free(temp);
	if (env_var == NULL)
		env_var = ft_calloc(1, 1);
	if (env_var == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strdup(str + ind + count);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(env_var + count * (*env_var != '\0'), temp, 2);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	str[ind] = '\0';
	str = ft_strjoin_free(str, temp, 0);
	if (str == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	return (expand(str));
}

char	*expand(char *str)
{
	int		ind;
	int		count;

	if (str == NULL)
		return (btree()->type = ERROR, NULL);
	ind = 0;
	count = 0;
	while (str[ind])
	{
		if (str[ind] == '\'' && ++ind)
			while (str[ind] != '\'')
				ind++;
		if (str[ind] == '$' && (ft_isalnum(str[ind + 1]) || str[ind + 1] == '?' || str[ind + 1] == '_'))
		{
			count++;
			if (str[ind + 1] == '?')
				return (expand_aux(str, ind, 2, NULL));
			while (ft_isalnum((str + ind)[count]) || (str + ind)[count] == '_')
				count++;
			return (expand_aux(str, ind, count, NULL));
		}
		ind++;
	}
	return (str);
}

void	get_here_doc(char *eof, int fd[2])
{
	char	*str;
	// char	strfinal[1024];
	int		len;

	len = ft_strlen(eof);
	str = readline("> ");
	while (ft_strncmp(str, eof, len + 1))
	{
		str = expand(str);
		write (fd[1], str, ft_strlen(str));
		write (fd[1], "\n", 1);
		free (str);
		str = readline("> ");
	}
	free (str);
	// read(fd[0], strfinal, 1023);
	// printf("%s", strfinal);
	close (fd[0]);
	close (fd[1]);
}
// "ola meu caro guerreiro $USER" is your true name '$USER' by any chance?

char	*quote(char *str)
{
	char	ch;
	int		ind;
	char	*ret;

	ret = str;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			ind = 0;
			ch = str[ind];
			ind++;
			while (str[ind] != ch)
				ind++;
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
			ft_memmove(str, str + 1, ft_strlen(str));
			str += ind - 1;
		}
		else
			str++;
	}
	return (ret);
}

// int	check_syntax(char **mat)
// {
// 
// }

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

void	print_wild(t_wild *head)
{
	while (head)
	{
		printf("%s\n", head->file);
		head = head->next;
	}
}

int	find_slash(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	check_end(char *big, char *little)
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

void	remove_non_dir(t_wild **head)
{
	t_wild *node;
	t_wild *next;

	while (head && *head && (*head)->d_type != 4)
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
		if (next->d_type != 4)
		{
			node->next = next->next;
			free (next->file);
			free (next);
		}
		else
			node = next;
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

void	free_all(char **mat, int count)
{
	int	ind;

	ind = 0;
	while (ind < count)
	{
		free(mat[ind]);
		ind++;	
	}
}

char	**bind_mat_lst_aux(char **mat, char **ret, int count, t_wild *head);

char	**bind_mat_lst(char **mat, int count, t_wild *head, int ind)
{
	char	**ret;

	if (head == NULL)
		return (mat);
	ind = ft_matlen(mat) + wildsize(head) - 1;
	printf("printing mat\n");
	ft_print_matrix(mat);
	printf("printing head\n");
	print_wild(head);
	printf("done printing\n\n");
	printf("safe\n");
	ret = malloc(sizeof(char *) * (ind + 1));
	if (ret == NULL)
		return (btree()->type = ERROR, NULL);
	printf("safe1\n");
	printf("%d\n", ind);
	ret[ind] = NULL;
	// sort_head(head);
	ret = bind_mat_lst_aux(mat, ret, count, head);
	wild_clear(head);
	return (ret);
}

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


char	**exp_wildcards(char **mat, int count, char *empty_str, t_wild *head)
{
	char	**pattern;
	char	*limit[2];
	int		ind[2];

	mat[count] = expand(mat[count]);
	if (btree()->type == ERROR)
		return (NULL);
	pattern = ft_giga_split(mat[count], '*'); // change to a special split
	if (pattern == NULL)
		return (btree()->type = ERROR, NULL);
	if (mat[count][0] == '*')
		limit[0] = empty_str;
	else
		limit[0] = *pattern;
	ind[0] = ft_strlen(mat[count]);
	ind[1] = ft_matlen(pattern);
	if (mat[count][ind[0] - (ind[0] > 0)] == '*')
		limit[1] = empty_str;
	else
		limit[1] = pattern[ind[1] - (ind[1] > 0)];
	head = read_dir("./", NULL, limit[0]);
	head = get_pattern(head, pattern + (*pattern == *limit), limit);
	return (bind_mat_lst(mat, count, head, 0));
}

char	**wildcards(char **mat, int ind, char ch, int count)
{
	char	**new;

	if (btree()->type == ERROR)
		return (NULL);
	if (mat[count] == NULL)
		return (mat);
	if (ft_strncmp(mat[count], "<<", 3) == 0)
		return (wildcards(mat, 0, 0, count + 2));
	while (mat[count][ind])
	{
		if ((mat[count][ind] == '\'' || mat[count][ind] == '\"') && ++ind)
		{
			ch = mat[count][ind];
			while (mat[count][ind] != ch)
				ind++;
		}
		if (mat[count][ind] == '*')
		{
			new = exp_wildcards(mat, count, "\0", NULL);
			count += ft_matlen(new) - ft_matlen(mat);
			return (wildcards(new, 0, 0, count + 1));
		}
		ind++;
	}
	return (wildcards(mat, 0, 0, count + 1));
}

int check_next(char *str);

int	check_parethesis(char **mat, int count)
{
	if (ft_strcmp(*mat, "(") == 0)
	{
		if (check_next(*(mat + 1)))
			return (write(1, "syntax error near unexpected token `('", 39));
		return (1);
	}
	if (ft_strcmp(*mat, ")") == 0)
	{
		if (count <= 0)
			return (write(1, "syntax error near unexpected token `)'", 39));
		if (*mat && ft_strcmp(*mat, "(") == 0)
			return (write(1, "syntax error near unexpected token `)'", 39));
		return (-1);
	}
}

int check_next(char *str)
{
	if (str && (!ft_strcmp(str, ")") || \
		!ft_strcmp(str, "&&") || !ft_strcmp(str, "||")) \
			|| !ft_strcmp(str, "|") || !ft_strcmp(str, "&"))
		return (1);
	return (0);
}
int	check_first(char **mat)
{
	if (!ft_strcmp(*mat, "&&") || !ft_strcmp(*mat, "||") || \
		!ft_strcmp(*mat, "&") || !ft_strcmp(*mat, "|") || \
			!ft_strcmp(*mat, ")"))
	{
		write(1, "syntax error near unexpected token `", 36);
		write(1, *mat, ft_strlen(*mat));
		write(1, "'", 2);
		return (1);
	}
	return (0);
}

int	syntax_error_msg(char *str)
{
	write(1, "syntax error near unexpected token `", 36);
	write(1, str, ft_strlen(str));
	write(1, "'", 2);
	return (1);
}

int	check_syntax(char **mat, t_token tokens)
{
	int	count;
	int	temp;

	if (check_first(mat))
		return (1);
	count = 0;
	while (*mat && *(mat + 1))
	{
		if (!ft_strcmp(*mat, ">") || !ft_strcmp(*mat, ">>") || \
			!ft_strcmp(*mat, "<") || !ft_strcmp(*mat, "<<"))
			if (find_tokens(*(mat + 1), tokens))
				return (syntax_error_msg(*(mat + 1)));
		temp = check_parethesis(mat, count);
		if (temp > 1 || temp < -1);
			return (1);
		count += temp;
	}
	if (check_last(mat))
		return (1);
	if (count > 0)
		return (write(1, "syntax error near unexpected token `)'", 39));
	if (count < 0)
		return (write(1, "syntax error near unexpected token `('", 39));
	return (0);
}

int	parsing(char *str)
{
	char	*stokens[] = {"(", ")", "&", "|", ">", "<", NULL};
	char	*dtokens[] = {"||", "&&", ">>", "<<", NULL};
	char	*sep[] = {"'", "\"", "`", NULL};
	char 	**mat;
	int		parethesis;
	t_token	tokens;

	if (str == NULL || *str == '\0')
		return (1);
	tokens.stokens = stokens;
	tokens.dtokens = dtokens;
	mat = tokenization(str, tokens, sep);
	if (mat == NULL)
		return (printf("mat is null\n"), 1);
	if (check_syntax(mat, tokens))
		return (1);
	while (parethesis)
	{
		mat =+ parethesis;
		parethesis += open_parethesis(mat);
	}
	init_tree(mat);
	create_binary_tree(mat, separator_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (binary_clear(btree()), 1);
	return (0);
}
