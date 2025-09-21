/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_strcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:38 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/04 14:38:39 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs_strcmp(char *str1, char *str2)
{
	char ch1;
	char ch2;

	if (!str1 || !str2)
		return (str1 - str2);
	while (*str1 && *str2)
	{
		ch1 = *str1 + (*str1 > 64 && *str1 < 91) * 32;
		ch2 = *str2 + (*str2 > 64 && *str2 < 91) * 32;
		if (ch1 != ch2)
			return (ch1 - ch2);
		str1++;
		str2++;
	}
	return (0);
}