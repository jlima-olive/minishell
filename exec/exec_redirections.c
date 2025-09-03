#include "../sigma_minishell.h"
#include <stdio.h>

int is_redir_token(const char *s)
{
	// printf("=======IS_REDIR_TOKEN SENDO RODADA IGUAL SUA MAE\n");
    return (strcmp(s, ">") == 0 || strcmp(s, ">>") == 0
         || strcmp(s, "<") == 0 || strcmp(s, "<<") == 0);
}

int has_redir(t_cmds *cmd)
{
    if (!cmd)
        return 0;
    if (cmd->infiles != NULL || cmd->outfiles != NULL)
        return 1;
    int i = 0;
    while (cmd->cmd && cmd->cmd[i])
    {
        if (is_redir_token(cmd->cmd[i]))
            return 1;
        i++;
    }
    return 0;
}

int count_tokens(t_cmds *cmd)
{
	// printf("========COUNTING\n");
    int i = 0, count = 0;
    while (cmd->cmd[i])
    {
        if (is_redir_token(cmd->cmd[i]) && cmd->cmd[i + 1])
            i += 2;
        else {
            count++;
            i++;
        }
    }
    return count;
}

char **array_to_exec(t_cmds *cmd)
{
    int i = 0, j = 0;

    if (!cmd || !cmd->cmd)
        return NULL;
	// printf("=======LANCANDO ARRAY TO EXEC\n");
    char **new_argv = malloc(sizeof(char *) * (count_tokens(cmd) + 1));
    if (!new_argv)
        return NULL;
    while (cmd->cmd[i])
    {
        if (is_redir_token(cmd->cmd[i]) && cmd->cmd[i + 1])
            i += 2;
        else
            new_argv[j++] = strdup(cmd->cmd[i++]);
    }
    new_argv[j] = NULL;
    return new_argv;
}

void exec_redirections(t_cmds *cmd)
{
    // INFILES
    for (t_infile *in = cmd->infiles; in; in = in->next) {
        if (strcmp(in->token, "<") == 0) {
            int fd = open(in->file, O_RDONLY);
            if (fd < 0) { perror(in->file); exit(1); }
            if (dup2(fd, STDIN_FILENO) < 0) { perror("dup2"); exit(1); }
            close(fd);
        } else if (strcmp(in->token, "<<") == 0) {
            int p[2];
            if (pipe(p) == -1) { perror("pipe"); exit(1); }
            get_here_doc(in->file, p); // already in your code
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
        }
    }

    // OUTFILES
    for (t_outfile *out = cmd->outfiles; out; out = out->next) {
        int flags = O_WRONLY | O_CREAT | (strcmp(out->token, ">>")==0 ? O_APPEND : O_TRUNC);
        int fd = open(out->file, flags, 0644);
        if (fd < 0) { perror(out->file); exit(1); }
        if (dup2(fd, STDOUT_FILENO) < 0) { perror("dup2"); exit(1); }
        close(fd);
    }
}





// int single_left(t_cmds *cmd)
// {

// }