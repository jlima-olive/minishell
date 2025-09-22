/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:22:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:42:52 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
