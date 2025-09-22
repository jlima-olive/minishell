/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_duper_hiper_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 11:49:12 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	free_matrix(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_env_node(t_os_envs *env)
{
	if (!env)
		return ;
	free(env->linux_envs);
	free(env);
}

void	free_env_list(t_os_envs *head)
{
	t_os_envs	*temp;

	while (head)
	{
		temp = head->next;
		free_env_list(head);
		head = temp;
	}
}
