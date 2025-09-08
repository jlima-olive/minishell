#include "../sigma_minishell.h"

int	check_parethesis(char **mat, int count)
{
	if (ft_strcmp(*mat, "(") == 0)
	{
		if (*(mat + 1) && (!ft_strcmp(*(mat + 1), ")") || \
			!ft_strcmp(*(mat + 1), "&&") || !ft_strcmp(*(mat + 1), "||") \
				|| !ft_strcmp(*(mat + 1), "|") || !ft_strcmp(*(mat + 1), "&")))
			return (write(1, "syntax error near unexpected token `('\n", 39));
		return (1);
	}
	if (ft_strcmp(*mat, ")") == 0)
	{
		if (count <= 0)
			return (write(1, "syntax error near unexpected token `)'\n", 39));
		if (*mat && ft_strcmp(*mat, "(") == 0)
			return (write(1, "syntax error near unexpected token `)'\n", 39));
		return (-1);
	}
	return (0);
}

int	check_first(char *str)
{
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||") || \
		!ft_strcmp(str, "&") || !ft_strcmp(str, "|") || \
			!ft_strcmp(str, ")"))
	{
		syntax_error_msg(str);
		return (1);
	}
	return (0);
}

int	check_last(char *str)
{
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||") || \
		!ft_strcmp(str, "|") || !ft_strcmp(str, "(") || \
			!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || \
				!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
	{
		syntax_error_msg("newline");
		return (1);
	}
	return (0);
}

int	check_tokens(char **mat, t_token tokens)
{
	if (!ft_strcmp(*mat, "&&") || !ft_strcmp(*mat, "||") || \
		!ft_strcmp(*mat, "|") || !ft_strcmp(*mat, "&"))
		if (!ft_strcmp(*(mat + 1), "&&") || !ft_strcmp(*(mat + 1), "||") || \
			!ft_strcmp(*(mat + 1), "|") || !ft_strcmp(*(mat + 1), "&") || \
				!ft_strcmp(*(mat + 1), ")"))
			return (syntax_error_msg(*(mat + 1)), 1);
	if (!ft_strcmp(*mat, ">") || !ft_strcmp(*mat, ">>") || \
		!ft_strcmp(*mat, "<") || !ft_strcmp(*mat, "<<"))
		if (find_tokens(*(mat + 1), tokens))
			return (syntax_error_msg(*(mat + 1)), 1);
	return (0);
}

int	check_syntax(char **mat, t_token tokens)
{
	int	count;
	int	temp;

	if (*mat && check_first(*mat))
		return (1);
	count = 0;
	while (*mat && *(mat + 1))
	{
		if (check_tokens(mat, tokens))
			return (syntax_error_msg(*(mat + 1)), 1);
		temp = check_parethesis(mat, count);
		if (temp > 1 || temp < -1)
			return (1);
		count += temp;
		mat++;
	}
	if (*mat && check_last(*mat))
		return (1);
	if (count > 0)
		return (write(1, "syntax error near unexpected token `)'\n", 39));
	if (count < 0)
		return (write(1, "syntax error near unexpected token `('\n", 39));
	return (0);
}
