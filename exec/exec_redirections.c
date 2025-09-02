#include "../sigma_minishell.h"

int is_redir_token(const char *s)
{
    return (strcmp(s, ">") == 0 || strcmp(s, ">>") == 0
         || strcmp(s, "<") == 0 || strcmp(s, "<<") == 0);
}

int has_redir(t_cmds *cmd)
{
    int i = 0;
    if (!cmd || !cmd->cmd)
        return 0;
    while (cmd->cmd[i])
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

void single_right(t_cmds *cmd)
{
    int fd;
    int i = 0;
    
    if (!cmd || !cmd->cmd)
        return;
    
    while (cmd->cmd[i])
    {
        if (strcmp(cmd->cmd[i], ">") == 0 && cmd->cmd[i + 1])
        {
            fd = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
            return; // Only handle the first occurrence
        }
        i++;
    }
}

void double_right(t_cmds *cmd)
{
    int fd;
    int i = 0;
    
    if (!cmd || !cmd->cmd)
        return;
    
    while (cmd->cmd[i])
    {
        if (strcmp(cmd->cmd[i], ">>") == 0 && cmd->cmd[i + 1])
        {
            fd = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
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
            return;
        }
        i++;
    }
}

void exec_redirections(t_cmds *cmd)
{
    if (!cmd || !cmd->cmd)
        return;
    
    single_right(cmd);
    double_right(cmd);
}

// int single_left(t_cmds *cmd)
// {

// }