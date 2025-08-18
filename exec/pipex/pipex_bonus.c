/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:19:15 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/24 11:24:43 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft/libft.h"

char	*get_here_doc(char *limiter)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = get_next_line(0);
	while (ft_strncmp(temp, limiter, ft_strlen(temp) - 1))
	{
		str = ft_strjoin_free(str, temp, 3);
		temp = get_next_line(0);
	}
	free(temp);
	return (str);
}

void	get_file(char *file, int wr)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		str = get_next_line(fd);
		while (str)
		{
			ft_putstr_fd(str, wr);
			free (str);
			str = get_next_line(fd);
		}
		close(fd);
	}
}

int	feed_file_into_pipe(int *fd, char **av, int to_close)
{
	int		id;
	char	*str;

	str = NULL;
	id = fork();
	if (id < 0)
		return (perror(strerror(errno)), exit(errno), 0);
	if (id == 0)
	{
		if (to_close > 0)
			close(to_close);
		if (ft_strncmp(av[0], "here_doc", 9))
			get_file(av[1], fd[1]);
		else
		{
			str = get_here_doc(av[1]);
			ft_putstr_fd(str, fd[1]);
			free(str);
		}
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	return (ft_strncmp(av[0], "here_doc", 9) && access(av[1], R_OK));
}

int	main(int ac, char **av, char **ev)
{
	t_pipex	data;

	data.fd[2] = check_input(&ac, &av, ev);
	if (pipe(data.fd) < 0)
		return (perror(strerror(errno)), close(data.fd[2]), errno);
	data.ind = 1 + feed_file_into_pipe(data.fd, av, data.fd[2]);
	while (++data.ind < ac - 2)
		data.id = pipe_into_pipe(av[data.ind], ev, data.fd, data.fd[2]);
	close(data.fd[1]);
	if ((check_one_cmd(av[ac - 2], ev, NULL, 1) == 0) && data.fd[2] > 0)
	{
		data.id = fork();
		if (data.id < 0)
			return (perror(strerror(errno)), exit(errno), 0);
		if (data.id == 0)
			rdwr_frm_int_fd(av[ac - 2], ev, data.fd[0], data.fd[2]);
	}
	while (--data.ind)
		wait(NULL);
	if (data.fd[2] > 0)
		close(data.fd[2]);
	close(data.fd[0]);
	data.ind = (check_one_cmd(av[ac - 2], ev, NULL, 1) != 0) * 127;
	return (data.ind * (data.fd[2] > 0) + (data.fd[2] < 0));
}
