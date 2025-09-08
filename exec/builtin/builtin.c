#include "../../sigma_minishell.h"


int is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "exit", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "unset", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", 6) == 0)
        return (1);
    return (0);
}

void builtin_cd(char *path) 
{
    if (path == NULL || path[0] == '\0') 
    {
        if (chdir(getenv("HOME")) != 0) 
            perror("cd");
    }
    else if (chdir(path) != 0) 
        perror("cd");
}

void builtin_pwd(void)
{
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) == NULL)
        perror("pwd");
    else
        printf("%s\n", buf);
}

void builtin_echo(char **args)
{
    int i;
    char *cleaned;

    i = 1;
    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
        i++;
    while (args[i])
    {
        cleaned = aspas(args[i]);
        printf("%s", cleaned);
        free(cleaned);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (!(args[1] && ft_strncmp(args[1], "-n", 2) == 0))
        printf(("\n"));
}

void    builtin_exit(char **args)
{
    int status;

    status = 0;
    if (args[1])
        status = ft_atoi(args[1]);
    exit (status);
}

int exec_builtin(char *cmd, char **args)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
            builtin_cd(args[1]);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        builtin_pwd();
    else if (ft_strncmp(cmd, "env", 3) == 0)
        print_env_list();
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        builtin_echo(args);
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        builtin_exit(args);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        builtin_unset(args);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        builtin_export(args);
    else
        return (0);
    return (0);
}