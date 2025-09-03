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
	printf("========COUNTING\n");
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
	printf("=======LANCANDO ARRAY TO EXEC\n");
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
    int i = 0;

    if (!cmd || !cmd->cmd)
        return;
    printf("=====OLA EU SOU EXEC_REDIRECTIONS\n");
    while (cmd->cmd[i])
    {
        printf("=====ESTOU DENTRO DO LOOP DO EXEC_REDIRECTIONS\n");
        if (strcmp(cmd->cmd[i], ">") == 0 && cmd->cmd[i + 1])
        {
            printf("==== ESTOU AQUI PQ O COMAND TEM > COMO REDIRECTION\n");
            int fd = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("open >");
                perror("===== ESTOU AQUI PQ O FD E MENOR DO QUE ZERO");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                printf("===== I AM INSIDE IF DUP LINE 80 EXEC REDIRECTIONS\n");
                perror("dup2 >");
                close(fd);
                exit(1);
            }
            close(fd);
            i += 2;
        }
        else if (strcmp(cmd->cmd[i], ">>") == 0 && cmd->cmd[i + 1])
        {
            printf("==== ESTOU AQUI PQ O COMAND TEM >> COMO REDIRECTION\n");
            int fd = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("===== ESTOU AQUI PQ O FD E MENOR DO QUE ZERO PARTE 2");
                perror("open >>");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                printf("===== I AM INSIDE IF DUP LINE 100 EXEC REDIRECTIONS\n");
                perror("dup2 >>");
                close(fd);
                exit(1);
            }
            close(fd);
            i += 2;
        }
        else if (strcmp(cmd->cmd[i], "<") == 0 && cmd->cmd[i + 1])
        {
            int fd = open(cmd->cmd[i + 1], O_RDONLY);
            if (fd < 0)
            {
                perror("open <");
                exit(1);
            }
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("dup2 <");
                close(fd);
                exit(1);
            }
            close(fd);
            i += 2;
        }
        else
            printf("===============AINDA NAO E UMA REDIRECTIONS\n"), i++;
    }
}


// int single_left(t_cmds *cmd)
// {

// }