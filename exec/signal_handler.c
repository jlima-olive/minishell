/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 17:14:23 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	// printf("HANDLE SIGINT\n");
	btree()->global_signal = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void set_to_onethirty(int sig)
{
	(void)sig;
	// printf("set one trusht\n");

	btree()->global_signal = 130;
	rl_replace_line("", 0);
}

void	handle_heredoc(int sig)
{
	(void)sig;
	// printf("HANDLE heredoc\n");

	close(0);
	btree()->global_signal = 130;
}

int restart_signals(void)
{
	// printf("restart\n");
	if (btree()->global_signal == 130)
		write (1, "\n", 1);
	signal(SIGINT, handle_sigint);
	btree()->global_signal = 0;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	return (0);
}