#include "sigma_minishell.h"
#include <dirent.h>

char	*teststrjoin(char const *s1, char const *s2)
{
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (strdup(s2));
	if (s2 == NULL)
		return (strdup(s1));
	ret = calloc(strlen((char *)s1) + strlen((char *)s2) + 1, 1);
	if (ret == NULL)
		return (NULL);
	ret = strcpy(ret, (char *)s1);
	ret = strcat(ret, (char *)s2);
	return (ret);
}

void	print_all(char *dir)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*temp;

	directory = opendir(dir);
	if (directory == NULL)
	{
		perror (dir);
		return ;
	}
	entry = readdir(directory);
	closedir(directory);
}

int	main(void)
{
}