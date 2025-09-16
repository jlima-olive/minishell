#include "../sigma_minishell.h"
#include <stdio.h>

int is_redir_token(const char *s)
{
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

int exec_redirections(t_cmds *cmd)
{
    t_infile *in = cmd->infiles;
    t_outfile *out;

    while (in)
    {
        if (ft_strcmp(in->token, "<") == 0)
        {
            int fd = open(in->file, O_RDONLY);
            if (fd < 0)
                return (perror(in->file), -1);
            if (dup2(fd, STDIN_FILENO) < 0)
                return (perror("dup2"), close(fd), -1);
            close(fd);
        }
        else if (ft_strcmp(in->token, "<<") == 0)
        {
            if (cmd->cmd)
            {
                int p[2];
                if (pipe(p) == -1)
                    return (perror("pipe"), -1);
                get_here_doc(in->file, p);      // write to pipe
                if (dup2(p[0], STDIN_FILENO) < 0)
                    return (perror("dup2"), close(p[0]), -1);
                close(p[0]);
                close(p[1]);
            }
            else
                get_here_doc(in->file, NULL);   // discard input
        }
        in = in->next;
    }
    out = cmd->outfiles;
    while (out)
    {
        int flags = O_WRONLY | O_CREAT;
        if (ft_strcmp(out->token, ">>") == 0)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
        int fd = open(out->file, flags, 0644);
        if (fd < 0 || !out->file)
            return (perror(out->file), -1);
        if (dup2(fd, STDOUT_FILENO) < 0)
            return (perror("dup2"), close(fd), -1);
        close(fd);
        out = out->next;
    }

    return 0;
}


