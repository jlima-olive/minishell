#include "../../sigma_minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;
	char	buf[1024];

	pwd = find_path_in_list(*get_env_list(), "PWD=");
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		if (getcwd(buf, sizeof(buf)) != NULL)
			printf("%s\n", buf);
		else
			return (perror("pwd"), 0);
	}
	return (0);
}