/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:08:05 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/19 16:08:06 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <stdio.h>

char	**array_to_exec(t_cmds *cmd)
{
	int		i;
	int		j;
	char	**new_argv;

	i = 0;
	j = 0;
	if (!cmd || !cmd->cmd)
		return (NULL);
	new_argv = malloc(sizeof(char *) * (count_tokens(cmd) + 1));
	if (!new_argv)
		return (NULL);
	while (cmd->cmd[i])
	{
		if (is_redir_token(cmd->cmd[i]) && cmd->cmd[i + 1])
			i += 2;
		else
			new_argv[j++] = strdup(cmd->cmd[i++]);
	}
	new_argv[j] = NULL;
	return (new_argv);
}

static int	exec_single_left(t_infile *in)
{
	int	fd;

	fd = open(in->file, O_RDONLY);
	if (fd < 0)
		return (perror(in->file), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
	return (0);
}

static int	exec_double_left(t_infile *in, t_cmds *cmd)
{
	int	p[2];

	if (cmd->cmd)
	{
		if (pipe(p) == -1)
			return (perror("pipe"), -1);
		get_here_doc(in->file, p);
		if (dup2(p[0], STDIN_FILENO) < 0)
			return (perror("dup2"), close(p[0]), -1);
		close(p[0]);
		close(p[1]);
	}
	else
		get_here_doc(in->file, NULL);
	return (0);
}

static int	exec_out_redirections(t_outfile *out)
{
	int	fd;
	int	flags;

	while (out)
	{
		flags = O_WRONLY | O_CREAT;
		if (ft_strcmp(out->token, ">") == 0)
			flags |= O_TRUNC;
		else if (ft_strcmp(out->token, ">>") == 0)
			flags |= O_APPEND;
		else
			return (fprintf(stderr, "Unknown redirection: %s\n", out->token),
				-1);
		fd = open(out->file, flags, 0644);
		if (fd < 0)
			return (perror(out->file), -1);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (perror("dup2"), close(fd), -1);
		close(fd);
		out = out->next;
	}
	return (0);
}

int	exec_redirections(t_cmds *cmd)
{
	t_infile	*in;
	t_outfile	*out;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<") == 0)
		{
			if (exec_single_left(in) < 0)
				return (-1);
		}
		else if (ft_strcmp(in->token, "<<") == 0)
		{
			if (exec_double_left(in, cmd) < 0)
				return (-1);
		}
		in = in->next;
	}
	out = cmd->outfiles;
	if (exec_out_redirections(out) < 0)
		return (-1);
	return (0);
}
