#include "../../sigma_minishell.h"
#include <readline/readline.h>


int count_it(char *str, int c)
{
	int i = 0;
	int count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char *remove_it(char *str, int c)
{
    int i = 0;
    int j = 0;
	if (!str)
		return (NULL);
    int count = count_it(str, c);
    char *removed = malloc(ft_strlen(str) + 1 - count);
    if (!removed)
        return (NULL);

    while (str[i])
    {
        if (str[i] != c)
        {
            removed[j] = str[i];
            j++;
        }
        i++;
    }
    removed[j] = '\0';
    return (removed);
}

void odd_aspas(char *str, char c)
{
	int count;
	count = count_it(str, c);
	if (count % 2 == 1)
	{
		while (1)
		{
			char *input = readline(">");
			if (!input)
				continue ;
			if (input[0] == c)
			{
				free(input);
				break ;
			}
			free(input);
		}
	}
}

char *aspas(char *str)
{
	if (!str)
		return (NULL);
	char *final_str = remove_it(str, '"');
	odd_aspas(str, '"');
	return (final_str);
}
