#ifndef JOJOMINISHELL_H
# define JOJOMINISHELL_H

#include "exec/minishell.h"
#include "parse/jojo_libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <dirent.h>

typedef struct s_wild
{
	char			*file;
	char			*search;
	char			d_type;
	struct	s_wild	*next;
}	t_wild;

typedef struct s_token
{
	char	**stokens;
	char	**dtokens;
}	t_token;

typedef struct s_outfile
{
	char				*token;
	char				*file;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_infile
{
	char 			*token;
	char			*file;
	struct s_infile	*next;
}	t_infile;

typedef struct s_os_envs_list{
	char				*linux_envs;
	char				*temp_vars;
	struct s_os_envs_list	*next;
}   t_os_envs_list;

typedef struct s_os_envs{
	char **linux_envs;
	char **temp_vars;
	struct s_os_envs *next;
}   t_os_envs;


int			is_builtin(char *cmd);
void		builtin_cd(char **args);
void		builtin_pwd(void);
void		builtin_exit(char **args);
int 		exec_builtin(char *cmd, char **args, char **envp);
void		print_env_list(void);
t_os_envs	**get_env_list(void);
void		builtin_export(char **args);
void		builtin_unset(char **args);
int				is_builtin(char *cmd);
void		builtin_exit(char **args);
void		print_env_list(void);
t_os_envs	**get_env_list(void);
void		builtin_export(char **args);
void		builtin_unset(char **args);
char		*aspas(char *str, int c);
void		handle_sigint(int sig);
void		print_linux_env_list(void);
char		*remove_it(char *str, int c);



typedef struct s_cmds
{
	int				expanded;
	char			**cmd;
	t_infile		*infiles;
	t_outfile		*outfiles;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_binary
{
	t_type			type;
	int				sublvl;
	int				left_ret;
	int				right_ret;
	int				subshell_ret;
	char			**mat;
	char			**env;
	t_cmds			*cmds;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
}	t_binary;

t_binary	*btree(void);
int			parsing(char *str);
void 		init_tree(char **mat);

char *aspas(char *str, int c);
int is_builtin(char *cmd);
void builtin_cd(char **args);
void builtin_pwd(void);
void builtin_echo(char **args);
void	builtin_exit(char **args);
void builtin_unset(char **args);
int exec_builtin(char *cmd, char **args, char **envp);
void builtin_export(char **args);
void print_env_list(void);
t_os_envs **get_env_list(void);
void builtin_env(char **env);
int exec_path(char *cmd, char **args, char **envp);
int exec_tree(t_binary *tree);
int	exec_pipes(t_cmds *cmd, char **env);
int	exec_redirections(t_cmds *cmd);
int has_redir(t_cmds *cmd);
void free_matrix(char **table);
char **array_to_exec(t_cmds *cmd);
char *find_path(char **envp, char *which_env);
void initialize_pwd(char **envp);
char *find_path_in_list(t_os_envs *env_list, const char *key);
void builtin_env(char **env);
int exec_path(char *cmd, char **args, char **envp);
int exec_tree(t_binary *tree);
int	exec_pipes(t_cmds *cmd, char **env);
int add_temp_var(const char *str);
char *remove_aspas(char *str);
void discard_heredoc(t_infile *infiles);

// struct_clear.c
void		binary_clear(t_binary *binary);
void		cmds_clear(t_cmds *cmds);
void		outfile_clear(t_outfile *outfile);
void		infile_clear(t_infile *infile);
void		wild_clear(t_wild *node);

// struct_new.c
t_binary	*binary_new(int shlvl, t_type type, t_binary *up, t_cmds *table);
t_cmds		*cmds_new(t_outfile *outfile, t_infile *infile, char **cmd);
t_outfile	*outfile_new(char *file, char *token);
t_infile	*infile_new(char *file, char *token);
t_wild		*wild_new(char *file, char d_type);

void		create_binary_tree(char **mat, int	shlvl, t_binary *tree);
t_outfile	*get_outfile(char **mat);
t_cmds		*get_cmds(char **mat);
void		create_binary_tree(char **mat, int	shlvl, t_binary *tree);
int			open_parethesis(char **mat);
void		*create_binary_lvl(char **mat, int id, t_binary *tree);

int	find_tokens(char *str, t_token tokens);

// wildcards.c
char	**bind_mat_lst(char **mat, int count, t_wild *head, int ind);
t_wild	*get_pattern(t_wild *head, char **pattern, char **limit);
void	remove_null(t_wild **head, t_wild *node, t_wild *next);
void	remove_non_start(t_wild **head, char *start, int len);
t_wild	*read_dir(char *dir, t_wild *head, char *start);
char	**wildcards(char **mat, int count, int flag);
void	remove_non_end(t_wild **head, char *end);
void	add_wild_back(t_wild **lst, t_wild *new);
int		hidden_files(char *file, char *start);
int		simple_syntax(char **mat);
void	sort_wild(t_wild *wild1);
void	quote_matrix(char **mat);
int		wildsize(t_wild *head);

// expansions.c
char	*expand(char *str);
char	*quote(char *str);

// syntax_error_msg.c
void	syntax_error_msg(char *str);

// get_pattern.c
t_outfile	*get_outfile(char **mat);
t_infile	*get_infile(char **mat);
int			find_pipe(char **mat);

// check_syntax.c
int	check_syntax(char **mat, t_token tokens);

// 
int	parsing_strlen(char *str, t_token tokens, char **sep);
int	word_count(char *str, t_token tokens, char **sep);

// future libft.h
char	*ft_matnstr(char **matrix, char *s, int n);
void	ft_matrix_uni(char **dest, char **src);

void			get_here_doc(char *eof, int fd[2]);

/*	this function receives char **environment and returns a t_os_envs_list *
	where every node in the list has as its content one string from
	environment the list itself contains every string from environment*/
t_os_envs_list	*get_env(char **environ);

#endif