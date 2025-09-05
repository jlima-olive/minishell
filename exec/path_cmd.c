#include "../sigma_minishell.h"
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

int exec_path(char *cmd, char **args, char **envp)
{
    if (exec_system_path(cmd, args, envp) == 0)
        return (0);
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, args, envp);
            return (perror("execve failed"), -1);
        }
    }
    else
    {
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, args, envp);
            return (perror("execve failed"), -1);
        }
    }
    printf("command not found\n");
    return (-1);
}

