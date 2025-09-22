/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigma_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:59:13 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/22 13:09:28 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGMA_MINISHELL_H
# define SIGMA_MINISHELL_H

# include "exec/minishell.h"
# include "parse/jojo_libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>

typedef struct s_wild
{
	char					*file;
	char					*search;
	char					d_type;
	struct s_wild			*next;
}							t_wild;

typedef struct s_token
{
	char					**stokens;
	char					**dtokens;
}							t_token;

typedef struct s_outfile
{
	char					*token;
	char					*file;
	struct s_outfile		*next;
}							t_outfile;

typedef struct s_infile
{
	char					*token;
	char					*file;
	struct s_infile			*next;
}							t_infile;

typedef struct s_os_envs
{
	char					*linux_envs;
	char					*temp_vars;
	struct s_os_envs		*next;
}							t_os_envs;

typedef struct s_cmds
{
	int						expanded;
	char					**cmd;
	t_infile				*infiles;
	t_outfile				*outfiles;
	struct s_cmds			*next;
}							t_cmds;

typedef struct s_binary
{
	char			*logic;
	t_type			type;
	int				sublvl;
	int				left_ret;
	int				right_ret;
	int				subshell_ret;
	char			*print_cmd;
	char			**mat;
	t_os_envs		*os_env;
	char			**env;
	t_cmds			*cmds;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
	struct termios orig_termios; //<-- VINI TESTEANDO UMA CRAZY THING
}	t_binary;

int							parsing(char *str);
int							is_builtin(char *cmd);
int							builtin_cd(char **args);
int							builtin_pwd(void);
int							builtin_echo(char **args);
int							builtin_exit(char **args, char **envp);
int							builtin_unset(char **args);
int							exec_builtin(char *cmd, char **args, char **envp);
int							builtin_export(char **args);
int							exec_path(char *cmd, char **args, char **envp);
int							exec_tree(t_binary *tree);
int							exec_pipes(t_cmds *cmd, char **env);
int							exec_redirections(t_cmds *cmd);
int							has_redir(t_cmds *cmd);
int							print_linux_env_list(void);
int							add_temp_var(const char *str);
int							update_shell_level(int amount);
int							make_update_env(const char *str);
int							am_i_truly_myself(const char *cmd);
int							has_builtin(t_cmds *cmd);
int							is_redir_token(const char *s);
int							count_tokens(t_cmds *cmd);
int							check_path_access(char *path, char *cmd);
int							is_system_path_command(char *cmd, char **envp);
int							exec_system_path(char *cmd, char **args,
								char **envp);
int							count_it(char *str, int c);
int							add_new_env_var(t_os_envs **env_list,
								const char *str);
int							exec_single_cmd_aux(t_cmds *cmd);
bool						is_n_flag(const char *arg);
void						init_tree(char **mat);
void						print_env_list(void);
void						free_matrix(char **table);
void						builtin_env(char **env);
void						initialize_pwd(char **envp);
void						handle_sigint(int sig);
void						update_env_var(const char *key, const char *value);
void						discard_heredoc(t_infile *infiles);
void						init_shell_meta(void);
void						enhanced_sort_wild_vini_goat(t_os_envs *envs);
void						my_ffprintf(char *cmd, char *which_message);
void						expand_agrs(t_cmds *cmd);
void						prepare_for_exec(void);
void						clear_env_list(void);
void						rebuild_env_list(t_os_envs **env_list,
								char **env_vars);
void						free_env_list(t_os_envs *head);
char						*aspas(char *str, int c);
char						*remove_it(char *str, int c);
char						*remove_aspas(char *str);
char						*find_path(char **envp, char *which_env);
char						*find_path_in_list(t_os_envs *env_list,
								const char *key);
char						*get_env_var(char *name, char **envp);
char						*logical_pwd_update(const char *oldpwd,
								const char *target);
char						**array_to_exec(t_cmds *cmd);
char						**list_to_char(t_os_envs *envs);
char						**get_paths_to_search(char **envp);
char						**split_path(char **envp);
t_binary					*btree(void);
t_os_envs					**get_env_list(void);
t_os_envs					*create_env_node(char *path);

// struct_clear.c
void						binary_clear(t_binary *binary);
void						cmds_clear(t_cmds *cmds);
void						outfile_clear(t_outfile *outfile);
void						infile_clear(t_infile *infile);
void						wild_clear(t_wild *node);

// struct_new.c
t_binary					*binary_new(int shlvl, t_type type, t_binary *up,
								t_cmds *table);
t_cmds						*cmds_new(t_outfile *outfile, t_infile *infile,
								char **cmd);
t_outfile					*outfile_new(char *file, char *token);
t_infile					*infile_new(char *file, char *token);
t_wild						*wild_new(char *file, char d_type);

void						create_binary_tree(char **mat, int shlvl,
								t_binary *tree);
t_outfile					*get_outfile(char **mat);
t_cmds						*get_cmds(char **mat);
void						create_binary_tree(char **mat, int shlvl,
								t_binary *tree);
int							open_parethesis(char **mat);
void						*create_binary_lvl(char **mat, int id,
								t_binary *tree);

int							find_tokens(char *str, t_token tokens);

// wildcards.c
char						**bind_mat_lst(char **mat, int count, t_wild *head,
								int ind);
t_wild						*get_pattern(t_wild *head, char **pattern,
								char **limit);
void						remove_null(t_wild **head, t_wild *node,
								t_wild *next);
void						remove_non_start(t_wild **head, char *start,
								int len);
t_wild						*read_dir(char *dir, t_wild *head, char *start);
char						**wildcards(char **mat, int count, int flag);
void						remove_non_end(t_wild **head, char *end);
void						add_wild_back(t_wild **lst, t_wild *new);
int							hidden_files(char *file, char *start);
int							simple_syntax(char **mat);
void						sort_wild(t_wild *wild1);
void						quote_matrix(char **mat);
int							wildsize(t_wild *head);

// expansions.c
char						*expand(char *str, int ind, int count, int flag);
char						*quote(char *str);

// syntax_error_msg.c
void						syntax_error_msg(char *str);

// get_pattern.c
t_outfile					*get_outfile(char **mat);
t_infile					*get_infile(char **mat);
int							find_pipe(char **mat);

// check_syntax.c
int							check_syntax(char **mat, t_token tokens);

//
int							parsing_strlen(char *str, t_token tokens,
								char **sep);
int							word_count(char *str, t_token tokens, char **sep);

// future libft.h
char						*ft_matnstr(char **matrix, char *s, int n);
void						ft_matrix_uni(char **dest, char **src);

void						get_here_doc(char *eof, int fd[2]);

/*	this function receives char **environment and returns a t_os_envs_list *
	where every node in the list has as its content one string from
	environment the list itself contains every string from environment*/
// t_os_envs_list	*get_env(char **environ);

#endif