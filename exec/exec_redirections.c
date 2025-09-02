#include "../sigma_minishell.h"

static int is_redir(const char *s)
{
    return (strcmp(s, ">") == 0 || strcmp(s, ">>") == 0 || strcmp(s, "<") == 0 || strcmp(s, "<<") == 0);
}

int count_tokens(char **argv)
{
    int i = 0, count = 0;
    while (argv[i])
    {
        if (is_redir(argv[i]) && argv[i + 1])
            i += 2;
        else {
            count++;
            i++;
        }
    }
    return count;
}

char **array_to_exec(char **argv)
{
    int i = 0, j = 0;

    if (!argv)
        return NULL;
    char **new_argv = malloc(sizeof(char *) * (count_tokens(argv) + 1));
    if (!new_argv)
        return NULL;
    while (argv[i])
    {
        if (is_redir(argv[i]) && argv[i + 1])
            i += 2;
        else
            new_argv[j++] = strdup(argv[i++]);
    }
    new_argv[j] = NULL;
    return new_argv;
}

void    single_right(t_cmds *cmd)
{
    int fd;
    int i = 0;
    char **cleaned;
    if (!cmd)
        return ;
    if (!cmd->cmd)
        return ;
    while (cmd->cmd[i])
    {
        if (strcmp(cmd->cmd[i], ">") == 0 && cmd->cmd[i + 1])
        {
            cmd->outfiles->file = cmd->cmd[i + 1];
            fd = open(cmd->outfiles->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("Can't deal with this file");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2");
                close(fd);
                exit(1);
            }
            close(fd);
        }
        i++;
    }
    cleaned = array_to_exec(cmd->cmd);
    free(cmd->cmd);
    cmd->cmd = cleaned;
}

void double_right(t_cmds *cmd)
{
    int fd;
    int i = 0;
    char **cleaned;
    if (!cmd)
        return ;
    if (!cmd->cmd)
        return ;
    while (cmd->cmd[i])
    {
        if (strcmp(cmd->cmd[i], ">>") == 0 && cmd->cmd[i + 1])
        {
            cmd->outfiles->file = cmd->cmd[i + 1];
            fd = open(cmd->outfiles->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2");
                close(fd);
                exit(1);
            }
            close(fd);
        }
        close(fd);
        i++;
    }
    cleaned = array_to_exec(cmd->cmd);
    free(cmd->cmd);
    cmd->cmd = cleaned;
}
