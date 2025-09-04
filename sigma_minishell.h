#ifndef JOJOMINISHELL_H
# define JOJOMINISHELL_H

#include "exec/minishell.h"
#include "parse/jojo_libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>


// << = 256
// >> = 255

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

typedef struct s_os_envs{
	char **linux_envs;
	struct s_os_envs *next;
}   t_os_envs;

int		is_builtin(char *cmd);
void	builtin_cd(char *path);
void	builtin_pwd(void);
void	builtin_env(void);
void	builtin_exit(char **args);
int exec_builtin(char *cmd, char **args);
void print_env_list(void);
t_os_envs **get_env_list(void);
void builtin_export(char **args);
void builtin_unset(char **args);
char *aspas(char *str);
void    handle_sigint(int sig);


typedef struct s_cmds
{
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

char *aspas(char *str);
int is_builtin(char *cmd);
void builtin_cd(char *path);
void builtin_pwd(void);
void builtin_echo(char **args);
void	builtin_exit(char **args);
void builtin_unset(char **args);
int exec_builtin(char *cmd, char **args);
void builtin_export(char **args);
void print_env_list(void);
t_os_envs **get_env_list(void);
void builtin_env(void);
int exec_path(char *cmd, char **args, char **envp);
int exec_tree(t_binary *tree);
int    exec_pipes(t_cmds *cmd, char **env);
void	exec_redirections(t_cmds *cmd);
int has_redir(t_cmds *cmd);
void free_matrix(char **table);
char **array_to_exec(t_cmds *cmd);

void		binary_clear(t_binary *binary);
void		cmds_clear(t_cmds *cmds);
void		outfile_clear(t_outfile *outfile);
void		infile_clear(t_infile *infile);

t_binary	*binary_new(int shlvl, t_type type, t_binary *up, t_cmds *table);
t_cmds		*cmds_new(t_outfile *outfile, t_infile *infile, char **cmd);
t_outfile	*outfile_new(char *file, char *token);
t_infile	*infile_new(char *file, char *token);

void	create_binary_tree(char **mat, int	shlvl, t_binary *tree);
t_outfile	*get_outfile(char **mat);
int	find_pipe(char **mat);
t_cmds	*get_cmds(char **mat);
void	create_binary_tree(char **mat, int	shlvl, t_binary *tree);
void	create_binary_lvl(char **mat, int id, t_binary *tree);

// future libft.h
void	ft_matrix_uni(char **dest, char **src);
char	*ft_matnstr(char **matrix, char *s, int n);

void	print_files(t_infile	*file);

void	get_here_doc(char *eof, int fd[2]);
char	*expand(char *str);
char	*expand_aux(char *str, int ind, int count);

#endif