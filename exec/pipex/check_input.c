/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:22:04 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/22 17:46:57 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft/libft.h"

int	check_one_cmd(char *str, char **env, char **cmd, int value)
{
	char	*cmd_path;
	int		ind;

	if (ft_wrdchr(str, '/') || *env == NULL)
		return (access(str, X_OK));
	env = ft_split(ft_strnmat(env, "PATH=", 5) + 5, ':');
	if (env == NULL)
		return (1);
	cmd = pipex_split(str, NULL, 0, 0);
	if (cmd == NULL)
		return (ft_free_matrix(env), 1);
	str = ft_strjoin("/", *cmd);
	if (str == NULL)
		return (ft_free_matrix(cmd), ft_free_matrix(env), 1);
	ind = -1;
	while (env[++ind] && value)
	{
		cmd_path = ft_strjoin (env[ind], str);
		if (cmd_path == NULL)
			return (free(str), ft_free_matrix(env), ft_free_matrix(cmd), 1);
		value = access(cmd_path, X_OK);
		free(cmd_path);
	}
	return (free (str), ft_free_matrix(cmd), ft_free_matrix(env), value);
}

int	full_access(char *file)
{
	int	fd;

	if (access(file, W_OK) == 0)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT);
	if (fd > 0)
	{
		close (fd);
		unlink (file);
		return (0);
	}
	return (1);
}

void	check_all_cmd(int ac, char **av, char **env)
{
	int	ind;
	int	value;

	if (ft_strncmp(av[0], "here_doc", 9) && (access(av[1], R_OK)))
		perror(av[1]);
	ind = 1 + (access(av[1], R_OK) != 0);
	while (av[++ind + 1 - (full_access(av[ac - 1]))])
	{
		if (ft_wrdchr(av[ind], '/') || *env == NULL || ft_emptystr(av[ind]))
			value = access(av[ind], X_OK);
		else
			value = check_one_cmd(av[ind], env, NULL, 1);
		if (value == 1)
			return (ft_putstr_fd("memory error\n", 2), exit(errno));
		else if (value == -1 && ft_wrdchr(av[ind], '/'))
			perror(av[ind]);
		else if (value == -1)
		{
			ft_putstr_fd(av[ind], 2);
			ft_putstr_fd(": command not found 2\n", 2);
		}
	}
}

int	check_input(int *ac, char ***av, char **env)
{
	int	fd;

	if (*ac < 2)
	{
		ft_putendl_fd("invalid number of arguments", 2);
		exit(0);
	}
	(*ac) -= (ft_strncmp((*av)[1], "here_doc", 9) == 0);
	(*av) += (ft_strncmp((*av)[1], "here_doc", 9) == 0);
	if (*ac < 5)
	{
		ft_putendl_fd("invalid number of arguments", 2);
		exit(0);
	}
	check_all_cmd(*ac, *av, env);
	if (ft_strncmp((*av)[0], "here_doc", 9))
		fd = open((*av)[*ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open((*av)[*ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		perror((*av)[*ac - 1]);
	return (fd);
}
