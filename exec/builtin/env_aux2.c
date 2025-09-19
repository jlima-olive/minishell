/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:01:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/20 00:02:01 by vvazzs           ###   ########.fr       */
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
	char	*export_arg;
	char	*args[3];
	char	*pwd_value;

	pwd_value = find_path(envp, "PWD=");
	if (!pwd_value)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			perror("getcwd");
			return ;
		}
		export_arg = malloc(strlen("PWD=") + strlen(buf) + 1);
		if (!export_arg)
			return ;
		strcpy(export_arg, "PWD=");
		strcat(export_arg, buf);
		args[0] = "export";
		args[1] = export_arg;
		args[2] = NULL;
		builtin_export(args);
		free(export_arg);
	}
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

void	expand_agrs(t_cmds *cmd)
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
	expand_agrs(cmd->next);
}
