/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:01:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 17:20:15 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	print_linux_env_list(void)
{
	t_os_envs	*current;

	current = *get_env_list();
	while (current)
	{
		if (current->linux_envs)
			printf("%s\n", current->linux_envs);
		current = current->next;
	}
	return (1);
}

void	initialize_pwd(char **envp)
{
	char	buf[1024];
	char	*pwd_value;
	char	*full;

	pwd_value = find_path(envp, "PWD=");
	if (!pwd_value)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			perror("getcwd");
			return ;
		}
		full = malloc(strlen("PWD=") + strlen(buf) + 1);
		if (!full)
			return ;
		ft_strcpy(full, "PWD=");
		ft_strcat(full, buf);
		add_new_env_var(get_env_list(), full);
		free(full);
	}
	else
		free(pwd_value);
}

char	*find_temp_var(const char *key)
{
	t_os_envs	*env;
	size_t		len;

	env = *get_env_list();
	len = strlen(key);
	while (env)
	{
		if (env->temp_vars && ft_strncmp(env->temp_vars, key, len) == 0
			&& env->temp_vars[len] == '=')
			return (env->temp_vars + len + 1);
		env = env->next;
	}
	return (NULL);
}

void	expand_args(t_cmds *cmd)
{
	char	**mat;
	char	**temp;
	int		ind;

	if (!cmd)
		return ;
	temp = cmd->cmd;
	mat = wildcards(temp, 0, 0);
	cmd->expanded = 0;
	if (temp != mat)
	{
		free_matrix_nodes(temp);
		cmd->expanded = 1;
	}
	else
	{
		ind = -1;
		while (mat[++ind])
			mat[ind] = quote(mat[ind]);
	}
	cmd->cmd = mat;
	expand_args(cmd->next);
}
