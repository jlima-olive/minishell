#include "../../sigma_minishell.h"

void	update_env_var(const char *key, const char *value)
{
	char	*arg;
	char	*args[3];

	arg = malloc(strlen(key) + strlen(value) + 1);
	if (!arg)
		return ;
	strcpy(arg, key);
	strcat(arg, value);
	args[0] = "export";
	args[1] = arg;
	args[2] = NULL;
	builtin_export(args);
	free(arg);
}

static char	*join_paths(const char *oldpwd, const char *target)
{
	char	*newpwd;
	size_t	len;

	len = strlen(oldpwd) + 1 + strlen(target) + 1;
	newpwd = malloc(len);
	if (!newpwd)
		return (NULL);
	sprintf(newpwd, "%s/%s", oldpwd, target);
	return (newpwd);
}

char	*logical_pwd_update(const char *oldpwd, const char *target)
{
	char	*newpwd;
	char	*slash;

	if (!oldpwd)
		return (NULL);
	if (strcmp(target, "..") == 0)
	{
		newpwd = strdup(oldpwd);
		if (!newpwd)
			return (NULL);
		slash = strrchr(newpwd, '/');
		if (slash && slash != newpwd)
			*slash = '\0';
		else
			*(slash + 1) = '\0';
		return (newpwd);
	}
	else if (strcmp(target, ".") == 0)
		return (strdup(oldpwd));
	else if (target[0] == '/')
		return (strdup(target));
	else
		return (join_paths(oldpwd, target));
}

