#include "../sigma_minishell.h"

/* void	print_wild(t_wild *head)
{
	while (head)
	{
		printf("%s\n", head->file);
		head = head->next;
	}
} */

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

void	single_error_msg(char wc)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(&wc, 2);
	ft_putstr_fd("'", 2);
}

char **tokenization(char *str, t_token tokens, char **sep, int wc)
{
	int		ind;
	int		strcount;
	char	**ret;

	if (wc < 0)
<<<<<<< HEAD
		return (printf("\nUnclosed |%c|\n", -wc), NULL);
	// QUANDO COLOCAS SINGLE QUOTES PROGRAMA NAO ENTRA NO > INPUT


=======
<<<<<<< HEAD
		return (single_error_msg(wc), NULL);
=======
		return (printf("\nUnclosed |%c|\n", -wc), NULL); //ISSO TA A DAR SEGFAULT QUANDO FAZES ECHO "SALV <-- POR EXEMPLO | VINI
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
	// printf("\nwords in the input ->|%d|\n", wc);
>>>>>>> cfee328 (pipes working, gotta fix bugs)
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
<<<<<<< HEAD
	mat = tokenization(str, tokens, sep);
	// for (int i = 0; mat[i]; i++)
	// 	printf("====PARSING TESTING: Token[%d]: |%s|\n", i, mat[i]);
	/*if (check_syntax(mat))
		return (1);
		btree()->type = ERROR;*/
=======
	mat = NULL;
	if (str != NULL && *str != '\0')
		mat = tokenization(str, tokens, sep, word_count(str, tokens, sep));
>>>>>>> 33b2c0a7851e0ab3b6b56f7a580ef6116ed92002
	if (mat == NULL)
		return (1);
	// printf("printing matrix\n");
	// ft_print_matrix(mat);
	// printf("done printing matrix\n");
	if (check_syntax(mat, tokens))
		return (1);
	init_tree(mat);
	create_binary_tree(mat, sep_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (1);
	return (0);
}
