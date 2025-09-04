#include "../sigma_minishell.h"

void	syntax_error_msg(char *str)
{
	write(1, "syntax error near unexpected token `", 36);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
}
