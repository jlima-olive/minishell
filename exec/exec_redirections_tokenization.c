/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_tokenization.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:06:00 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/19 16:08:41 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	is_redir_token(const char *s)
{
	return (strcmp(s, ">") == 0 || strcmp(s, ">>") == 0 || strcmp(s, "<") == 0
		|| strcmp(s, "<<") == 0);
}

int	has_redir(t_cmds *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	if (cmd->infiles != NULL || cmd->outfiles != NULL)
		return (1);
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (is_redir_token(cmd->cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	count_tokens(t_cmds *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->cmd[i])
	{
		if (is_redir_token(cmd->cmd[i]) && cmd->cmd[i + 1])
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
