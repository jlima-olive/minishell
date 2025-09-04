#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"


/* void	print_wild(t_wild *head)
{
	while (head)
	{
		printf("%s\n", head->file);
		head = head->next;
	}
} */

int	find_tokens(char *str, t_token tokens)
{
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
			count++;
			ind += token_found;
		}
		else if (find_tokens(str + ind, tokens) == 0 && str[ind] && \
			(str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			count++;
			while (find_tokens(str + ind, tokens) == 0 && str[ind] && \
				(str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
			{
				sep_found = ft_matnstr(sep, str + ind, 1);
				if (sep_found && ++ind)
				{
					while (str[ind] != *sep_found && str[ind])
						ind++;
					if (str[ind] == '\0')
						return (-(*sep_found));
					ind++;
				}
				else
					ind++;
			}
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

char **tokenization(char *str, t_token tokens, char **sep, int wc)
{
	int		ind;
	int		strcount;
	char	**ret;

	if (wc < 0)
		return (fprintf(stderr, "syntax error near unexpected token `%c'", -wc), NULL);
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
		return (btree()->type = ERROR, NULL);
	return (expand(str));
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
		write (fd[1], "\n", 1); // idk if this is necessary perhaps it isnt
		free (str);
		str = readline("> ");
	}
	free (str);
	// read(fd[0], strfinal, 1023);	// this is just to test if its working
	// printf("%s", strfinal);		// this is just to test if its working
	close (fd[0]);
	close (fd[1]);
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

int	parsing(char *str)
{
	char	*stokens[] = {"(", ")", "&", "|", ">", "<", NULL};
	char	*dtokens[] = {"||", "&&", ">>", "<<", NULL};
	char	*sep[] = {"'", "\"", "`", NULL};
	char 	**mat;
	t_token	tokens;

	if (str == NULL || *str == '\0')
		return (1);
	tokens.stokens = stokens;
	tokens.dtokens = dtokens;
	mat = NULL;
	if (str != NULL && *str != '\0')
		mat = tokenization(str, tokens, sep, word_count(str, tokens, sep));
	if (mat == NULL)
		return (1);
	if (check_syntax(mat, tokens))
		return (1);
	init_tree(mat);
	create_binary_tree(mat, separator_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (1);
	return (0);
}
