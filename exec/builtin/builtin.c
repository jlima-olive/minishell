#include "../../sigma_minishell.h"
#include <stdlib.h>
#include <unistd.h>

int is_builtin(char *cmd)
{
	if (!cmd)
		return (write(2, "cmd is empty\n", 14), 0);
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return (1);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd, "env", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        return (1);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        return (1);
	else
    	return (0);
}

int has_builtin(t_cmds *cmd)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return (0);
    return (is_builtin(cmd->cmd[0]));
}

char *logical_pwd_update(const char *oldpwd, const char *target)
{
    char *newpwd;
    char *slash;

    if (!oldpwd)
        return NULL;

    if (strcmp(target, "..") == 0)
    {
        newpwd = strdup(oldpwd);
        if (!newpwd)
            return NULL;
        slash = strrchr(newpwd, '/');
        if (slash && slash != newpwd)
            *slash = '\0';
        else
            *(slash + 1) = '\0';
        return newpwd;
    }
    else if (strcmp(target, ".") == 0)
        return strdup(oldpwd);
    else if (target[0] == '/')
        return strdup(target);
    else
    {
        newpwd = malloc(strlen(oldpwd) + 1 + strlen(target) + 1);
        if (!newpwd)
            return NULL;
        sprintf( newpwd, "%s/%s", oldpwd, target);
        return newpwd;
    }
}

int builtin_cd(char **args)
{
    char *oldpwd = find_path_in_list(*get_env_list(), "PWD=");
    char buf[1024];
    char *target;
    char *newpwd = NULL;

    if (!args[1] || args[1][0] == '\0')
    {
        target = find_path_in_list(*get_env_list(), "HOME=");
        if (!target)
            return ( my_ffprintf(target, "cd: HOME not set\n"), 1);
    }
    else if (strcmp(args[1], "-") == 0)
    {
        target = find_path_in_list(*get_env_list(), "OLDPWD=");
        if (!target)
            return (my_ffprintf(target, "cd: OLDPWD not set\n"), 1);
        printf( "%s\n", target);
    }
    else
        target = args[1];
    if (chdir(target) != 0)
        return (perror("cd"), 1);
    if (oldpwd)
        update_env_var("OLDPWD=", oldpwd);
    if (getcwd(buf, sizeof(buf)) != NULL)
        update_env_var("PWD=", buf);
    else
    {
        newpwd = logical_pwd_update(oldpwd, target);
        if (newpwd)
        {
            update_env_var("PWD=", newpwd);
            free(newpwd);
        }
        else
            fprintf( stderr, "cd: failed to update PWD\n");
    }
	return (0);
}

int builtin_echo(char **args)
{
    int i = 1;
    int suppress_newline = 0;

    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
    {
        suppress_newline = 1;
        i++;
    }
    while (args[i])
    {
        char *arg = args[i];
        char *output;
        output = ft_strdup(arg);
        ft_putstr_fd(output, 1);
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!suppress_newline)
        write(1, "\n", 1);
	return (0);
}

int builtin_exit(char **args, char **envp)
{
    int status = 0;

    if (args[1])
        status = ft_atoi(args[1]);

    update_shell_level(-1);
    exit(status);
}


int exec_builtin(char *cmd, char **args, char **envp)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
            return builtin_cd(args);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        return builtin_pwd();
    else if (ft_strncmp(cmd, "env", 3) == 0)
        return print_linux_env_list();
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        return builtin_echo(args);
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        return builtin_exit(args, envp);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        return builtin_unset(args);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        return (builtin_export(args));
    return (1);
}
