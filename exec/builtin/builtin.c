#include "../../sigma_minishell.h"
#include <stdlib.h>
#include <unistd.h>

int is_builtin(char *cmd)
{
	// printf("")
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

void update_env_var(const char *key, const char *value)
{
    char *arg;
    char *args[3];

    arg = malloc(strlen(key) + strlen(value) + 1);
    if (!arg)
        return;
    strcpy(arg, key);
    strcat(arg, value);
    args[0] = "export";
    args[1] = arg;
    args[2] = NULL;
    builtin_export(args);
    free(arg);
}

static char *logical_pwd_update(const char *oldpwd, const char *target)
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
            *(slash + 1) = '\0'; // keep "/" root intact
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
        sprintf(newpwd, "%s/%s", oldpwd, target);
        return newpwd;
    }
}

void builtin_cd(char **args)
{
    char *oldpwd = find_path_in_list(*get_env_list(), "PWD=");
    char buf[1024];
    char *target;
    char *newpwd = NULL;

    if (!args[1] || args[1][0] == '\0')
    {
        target = find_path_in_list(*get_env_list(), "HOME=");
        if (!target)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        target = find_path_in_list(*get_env_list(), "OLDPWD=");
        if (!target)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return;
        }
        printf("%s\n", target); // bash prints path when using "cd -"
    }
    else
        target = args[1];

    if (chdir(target) != 0)
    {
        perror("cd");
        return;
    }

    // update OLDPWD
    if (oldpwd)
        update_env_var("OLDPWD=", oldpwd);

    // try to get absolute path
    if (getcwd(buf, sizeof(buf)) != NULL)
        update_env_var("PWD=", buf);
    else
    {
        // fallback: logical pwd update
        newpwd = logical_pwd_update(oldpwd, target);
        if (newpwd)
        {
            update_env_var("PWD=", newpwd);
            free(newpwd);
        }
        else
            fprintf(stderr, "cd: failed to update PWD\n");
    }
}


void builtin_pwd(void)
{
    char *pwd = find_path_in_list(*get_env_list(), "PWD=");
    if (pwd)
        printf("%s\n", pwd);
    else
    {
        char buf[1024];
        if (getcwd(buf, sizeof(buf)) != NULL)
            printf("%s\n", buf);
        else
            perror("pwd");
    }
}

void builtin_echo(char **args)
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
        int single_quoted = 0;
        int double_quoted = 0;
        if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
        {
            single_quoted = 1;
            arg = remove_it(arg, '\'');
        }
        else if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
        {
            double_quoted = 1;
            arg = remove_it(arg, '"');
        }
        char *output;
        if (single_quoted)
            output = ft_strdup(arg);
        else
            output = expand(arg);
        ft_putstr_fd(output, 1);
        // free(output);
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!suppress_newline)
        write(1, "\n", 1);
}

void builtin_exit(char **args, char **envp)
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
            builtin_cd(args);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        builtin_pwd();
    else if (ft_strncmp(cmd, "env", 3) == 0)
        print_linux_env_list();
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        builtin_echo(args);
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        builtin_exit(args, envp);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        builtin_unset(args);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        builtin_export(args);
    else
        return (0);
    return (0);
}
