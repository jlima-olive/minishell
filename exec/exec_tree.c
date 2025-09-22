/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:51:02 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec_child(t_cmds *cmd)
{
	char	**cleaned;
	char	**updated_envs;

	cleaned = array_to_exec(cmd);
	updated_envs = list_to_char(*get_env_list());
	if (has_redir(cmd))
		exec_redirections(cmd);
	if (has_builtin(cmd))
		exit(exec_builtin(cleaned[0], cleaned, updated_envs));
	else
		exec_path(cleaned[0], cleaned, updated_envs);
	free_matrix(cleaned);
	free_matrix(updated_envs);
}

int	exec_single_cmd(t_cmds *cmd)
{
	pid_t	pid;
	int		status;

	if (has_builtin(cmd) && !has_redir(cmd))
		return (exec_single_cmd_aux(cmd));
	pid = fork();
	if (pid == 0)
		exec_child(cmd);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		return (WEXITSTATUS(status));
	}
	return (1);
}

static int	exec_subshell(t_binary *subshell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(exec_tree(subshell));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	exec_node(t_binary *node)
{
	if (!node)
		return (0);
	if (node->cmds != NULL)
	{
		expand_agrs(node->cmds);
		if (node->cmds->next)
			return (exec_pipes(node->cmds, btree()->env));
		else
			return (exec_single_cmd(node->cmds));
	}
	if (node->subshell != NULL)
		return (exec_subshell(node->subshell));
	return (0);
}

int	exec_tree(t_binary *tree)
{
	int	ret_left;

	if (!tree)
		return (0);
	if (tree->logic && strcmp(tree->logic, "&&") == 0)
	{
		ret_left = exec_tree(tree->left);
		if (ret_left == 0)
			return (exec_tree(tree->right));
		return (ret_left);
	}
	if (tree->logic && strcmp(tree->logic, "||") == 0)
	{
		ret_left = exec_tree(tree->left);
		if (ret_left != 0)
			return (exec_tree(tree->right));
		return (ret_left);
	}
	return (exec_node(tree));
}
