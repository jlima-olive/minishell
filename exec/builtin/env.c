/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:02:43 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/20 00:10:56 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	get_current_shell_level(void)
{
	t_os_envs	*current;
	int			level;

	current = *get_env_list();
	level = 0;
	while (current)
	{
		if (current->linux_envs && strncmp(current->linux_envs, "SHLVL=",
				6) == 0)
		{
			level = ft_atoi(current->linux_envs + 6);
			break ;
		}
		current = current->next;
	}
	return (level);
}

int	update_shell_level(int amount)
{
	int		level;
	char	*num;
	char	*final_str;
	int		result;

	level = get_current_shell_level();
	level += amount;
	if (level < 0)
		level = 0;
	num = ft_itoa(level);
	if (!num)
		return (-1);
	final_str = malloc(strlen("SHLVL=") + strlen(num) + 1);
	if (!final_str)
		return (free(num), -1);
	strcpy(final_str, "SHLVL=");
	strcat(final_str, num);
	free(num);
	result = make_update_env(final_str);
	free(final_str);
	return (result);
}
