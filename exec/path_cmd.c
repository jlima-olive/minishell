#include "../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

char *find_path(char **envp, char *which_env)
{
    int i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], which_env, (strlen(which_env))) == 0)
            return (strdup(envp[i] + strlen(which_env)));
        i++;
    }
    return (NULL);
}

char **split_path(char **envp)
{
    char *path = find_path(envp, "PATH=");
    if (!path)
        return (NULL);
    char **vars = ft_split(path, ':');
    free(path);
    return (vars);
}

int exec_system_path(char *cmd, char **args, char **envp)
{
    char **paths_to_search = split_path(envp);
    if (!paths_to_search)
    {
        write(2, "PATH not found\n", 15);
        return -1;
    }
    int i = 0;
    while (paths_to_search[i])
    {
        char *full_path = malloc(strlen(paths_to_search[i]) + strlen(cmd) + 2);
        if (!full_path)
        {
            perror("malloc failed");
            int j = 0;
            while (paths_to_search[j])
                free(paths_to_search[j++]);
            free(paths_to_search);
            return -1;
        }
        strcpy(full_path, paths_to_search[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            execve(full_path, args, envp);
            perror("execve failed");
            free(full_path);
            int j = 0;
            while (paths_to_search[j])
                free(paths_to_search[j++]);
            free(paths_to_search);
            return -1;
        }
        free(full_path);
        i++;
    }
    i = 0;
    while (paths_to_search[i])
        free(paths_to_search[i++]);
    free(paths_to_search);
    return (-1);
}


char *get_env_var(char *name, char **envp)
{
    int len = strlen(name);
    for (int i = 0; envp[i]; i++)
    {
        if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return envp[i] + len + 1; // return value after '='
    }
    return NULL;
}

int update_shell_level(int amount, char **envp)
{
    char *current = get_env_var("SHLVL", envp);
    int level = 0;
    char *level_str;
    char *arg;
    char *args[3];

    if (current)
        level = ft_atoi(current);
    level += amount;
    if (level < 0)
        level = 0;
    level_str = ft_itoa(level);
    if (!level_str)
        return (-1);

    arg = malloc(strlen("SHLVL=") + strlen(level_str) + 1);
    if (!arg)
        return (-1);

    strcpy(arg, "SHLVL=");
    strcat(arg, level_str);

    args[0] = "export";
    args[1] = arg;
    args[2] = NULL;
    builtin_export(args);

    free(level_str);
    free(arg);
    return (0);
}


int exec_path(char *cmd, char **args, char **envp)
{
    if (cmd[0] == '$')
    {
        char *value = get_env_var(cmd + 1, envp);
        if (value)
        {
            printf("%s\n", value);
            return 0;
        }
        else
        {
            printf("Variable not found\n");
            return -1;
        }
    }
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, args, envp);
            perror("execve failed");
            return -1;
        }
    }
    else
    {
        if (strcmp(cmd, "./minishell") == 0)
            update_shell_level(1, envp);
        if (exec_system_path(cmd, args, envp) == 0)
            return 0;
    }
    printf("command not found\n");
    return -1;
}
