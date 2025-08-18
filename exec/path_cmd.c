#include "../sigma_minishell.h"

char *find_path(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return (strdup(envp[i] + 5));
        i++;
    }
    return (NULL);
}

char **split_path(char **envp)
{
    char *path = find_path(envp);
    if (!path)
        return (NULL);
    char **vars = ft_split(path, ':');
    free(path);
    return (vars);
}

void exec_path(char *cmd, char **args, char **envp)
{
    pid_t pid = fork();
    if (pid <= -1)
        return (perror("fork failed"));
    else if (pid == 0)
    {
        char **paths_to_search = split_path(envp);
        if (!paths_to_search)
        {
            write(2, "PATH not found\n", 15);
            exit(1);
        }
        int i = 0;
        while (paths_to_search[i])
        {
            char *full_path = malloc(strlen(paths_to_search[i]) + strlen(cmd) + 2);
            if (!full_path)
				perror("malloc failed"), exit(1);
			strcpy(full_path, paths_to_search[i]);
			strcat(full_path, "/");  
			strcat(full_path, cmd); 
            if (access(full_path, X_OK) == 0)
            {
                execve(full_path, args, envp);
                perror("execve failed");
                free(full_path);
                exit(1);
            }
            free(full_path);
            i++;
        }
        i = 0;
        while (paths_to_search[i])
            free(paths_to_search[i++]);
        free(paths_to_search);
        write(2, "command not found\n", 18);
        exit(1);
    }
    else
        waitpid(pid, NULL, 0);
}
