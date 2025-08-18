/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:20:52 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/06 16:35:00 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <limits.h> 
# include <fcntl.h> 
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_gln_strjoin(char *s1, char *s2);
int		zero_read(int fd, char *keep);
void	next_lines(char *ret);
int		ft_gnl_strlen(char *str);
int		check(char *str);

#endif