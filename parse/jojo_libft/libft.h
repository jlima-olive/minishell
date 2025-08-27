/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:02:51 by jlima-so          #+#    #+#             */
/*   Updated: 2025/08/27 19:02:38 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line/get_next_line_bonus.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <ctype.h>
# include <string.h>
// # include <bsd/string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_exec
{
	char	*path;
	char	**cmd;
	char	*str;
	int		ind;
	int		check;
	char	**mat;
}				t_exec;

typedef struct s_main
{
	int	fd;
	int	fd2[2];
	int	id;
	int	ind;
}	t_main;

typedef struct s_pipex
{
	int	fd[3];
	int	id;
	int	ind;
}	t_pipex;

void	ft_matrix_uni(char **dest, char **src);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_striteri(char const *s, void (*f)(unsigned int, char*));
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);
int		ft_atoi(const char *str);
void	ft_print_matrix(char **matrix);
void	ft_free_matrix(char **matrix);
void	ft_free_matrix_count(char **mat, int count);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strnmat(char **matrix, char *s, int n);
char	*ft_strmat(char **matrix, char *s);
char	*ft_strjoin_free(char *s1, char *s2, int flag);
int		ft_matlen(char **mat);
char	*ft_strndup(char *str, int ind);
char	**pipex_split(char *str, char **ret, int count, int loop);
int		pipe_into_pipe(char *av, char **env, int *fd, int to_close);
int		feed_file_into_pipe(int *fd, char **av, int to_close);
int		check_input(int *ac, char ***av, char **env);
int		check_one_cmd(char *str, char **env, char **cmd, int value);
void	rdwr_frm_int_fd(char *cmd_path_inc, char **env, int rd, int wr);
char	*ft_wrdchr(const char *s, int c);
int		ft_emptystr(const char *str);
int		ft_str_count(char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	adeus(void *content);

#endif