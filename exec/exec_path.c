#include "../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

char	*find_path(char **envp, char *which_env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], which_env, (ft_strlen(which_env))) == 0)
			return (ft_strdup(envp[i] + ft_strlen(which_env)));
		i++;
	}
	return (NULL);
}

char	**split_path(char **envp)
{
	char	*path;
	char	**vars;

	path = find_path(envp, "PATH=");
	if (!path)
		return (NULL);
	vars = ft_split(path, ':');
	free(path);
	return (vars);
}
static char	**get_paths_to_search(char **envp)
{
	return (split_path(envp));
}

static int	check_path_access(char *path, char *cmd)
{
	char	*full_path;
	int		result;

	full_path = malloc(strlen(path) + strlen(cmd) + 2);
	if (!full_path)
	{
		perror("malloc failed");
		return (-1);
	}
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	result = (access(full_path, X_OK) == 0);
	free(full_path);
	return (result);
}

int	is_system_path_command(char *cmd, char **envp)
{
	char	**paths_to_search;
	int		i;
	int		access_result;

	paths_to_search = get_paths_to_search(envp);
	if (!paths_to_search)
		return (-1);
	i = 0;
	while (paths_to_search[i])
	{
		access_result = check_path_access(paths_to_search[i], cmd);
		if (access_result == -1)
		{
			free_matrix(paths_to_search);
			return (-1);
		}
		if (access_result == 1)
		{
			free_matrix(paths_to_search);
			return (1);
		}
		i++;
	}
	free_matrix(paths_to_search);
	return (0);
}


void	prepare_for_exec(void)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &btree()->orig_termios) == -1)
			perror("tcsetattr");
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	exec_system_path(char *cmd, char **args, char **envp)
{
	int		i;
	int		j;
	char	**paths_to_search;
	char	*full_path;

	paths_to_search = split_path(envp);
	if (!paths_to_search)
	{
		write(2, "PATH not found\n", 15);
		return (-1);
	}
	i = 0;
	while (paths_to_search[i])
	{
		full_path = malloc(strlen(paths_to_search[i]) + strlen(cmd) + 2);
		if (!full_path)
		{
			perror("malloc failed");
			j = 0;
			while (paths_to_search[j])
				free(paths_to_search[j++]);
			free(paths_to_search);
			return (-1);
		}
		strcpy(full_path, paths_to_search[i]);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				prepare_for_exec();
				execve(full_path, args, envp);
				perror(full_path);
				free(full_path);
				j = 0;
				while (paths_to_search[j])
					free(paths_to_search[j++]);
				free(paths_to_search);
				return (-1);
			}
			else
				return (perror("permission denied"), -1);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths_to_search[i])
		free(paths_to_search[i++]);
	free(paths_to_search);
	return (-1);
}

char	*get_env_var(char *name, char **envp)
{
	int	len;

	len = strlen(name);
	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1); // return value after '='
	}
	return (NULL);
}

int	am_i_truly_myself(const char *cmd)
{
	char	*real;
	char	*self;
	int		result;

	real = realpath(cmd, NULL);
	self = realpath("/proc/self/exe", NULL);
	result = real && self && strcmp(real, self) == 0;
	free(real);
	free(self);
	return (result);
}

void	my_ffprintf(char *cmd, char *which_message)
{
	write(2, "bash: ", 7);
	write(2, which_message, ft_strlen(which_message));
}

int	exec_path(char *cmd, char **args, char **envp)
{
	char	*value;
					char *new_args[3];

	if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd,
			X_OK) == 0)
		update_shell_level(1);
	if (cmd[0] == '$')
	{
		value = get_env_var(cmd + 1, envp);
		if (strchr(value, '/'))
		{
			prepare_for_exec();
			execve(value, args, envp);
			my_ffprintf(cmd, "No such file or directory\n");
			return (-1);
		}
		else
		{
			prepare_for_exec();
			execve(value, args, envp);
			my_ffprintf(cmd, "command not found\n");
			return (-1);
		}
	}
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				prepare_for_exec();
				execve(cmd, args, envp);
				perror(cmd);
				return (-1);
			}
		}
	}
	if (is_system_path_command(cmd, envp))
	{
		if (exec_system_path(cmd, args, envp) == 0)
			return (0);
	}
	else
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				prepare_for_exec();
				execve(cmd, args, envp);
				if (errno == ENOEXEC)
				{
					new_args[0] = "/bin/bash";
					new_args[1] = cmd;
					new_args[2] = NULL;
					prepare_for_exec();
					execve(new_args[0], new_args, envp);
				}
				perror(cmd);
				return (-1);
			}
			else
				return (perror("minishell"), -1);
		}
	}
	printf("command not found\n");
	return (-1);
}
