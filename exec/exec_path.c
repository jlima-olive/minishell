#include "../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

struct shell_meta bash_meta;
struct shell_meta zsh_meta;

char *find_path(char **envp, char *which_env)
{
    int i = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], which_env, (ft_strlen(which_env))) == 0)
				return (ft_strdup(envp[i] + ft_strlen(which_env)));
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

int is_system_path_command(char *cmd, char **envp)
{

    char **paths_to_search = split_path(envp);
    if (!paths_to_search)
        return (-1);
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
            free(full_path);
            int j = 0;
            while (paths_to_search[j])
                free(paths_to_search[j++]);
            free(paths_to_search);
            return 1; // found in PATH
        }

        free(full_path);
        i++;
    }
    i = 0;
    while (paths_to_search[i])
        free(paths_to_search[i++]);
    free(paths_to_search);

    return 0; // not found in PATH
}

void prepare_for_exec(void)
{
    if (isatty(STDIN_FILENO))
    {
        if (tcsetattr(STDIN_FILENO, TCSANOW, &btree()->orig_termios) == -1)
            perror("tcsetattr");
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
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
        if (access(full_path, F_OK) == 0)
        {
            if (access(full_path, X_OK) == 0)
            {
                prepare_for_exec();
                execve(full_path, args, envp);
                perror("execve failed 1");
                free(full_path);
                int j = 0;
                while (paths_to_search[j])
                    free(paths_to_search[j++]);
                free(paths_to_search);
                return -1;
            }
            else
                return (perror("permission denied"), -1);
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

int am_i_truly_myself(const char *cmd)
{
    char *real = realpath(cmd, NULL);
    char *self = realpath("/proc/self/exe", NULL);
    int result = real && self && strcmp(real, self) == 0;
    free(real);
    free(self);
    return result;
}


void my_fprintf(char *cmd, char *which_message)
{
    char *expanded = expand(cmd, 0, 0, 1);
    write(2, "bash: ", 7);
    write(2, expanded, ft_strlen(expanded));
    write(2, ": ", 2);
    // write(2, strerror(errno), ft_strlen(strerror(errno)));
    // write(2, "\n", 1);
    write(2, which_message, ft_strlen(which_message));
}

void init_shell_meta(void) {
    struct stat st;

    // Try Bash
    if (stat("/bin/bash", &st) == 0) {
        bash_meta.st_dev = st.st_dev;
        bash_meta.st_ino = st.st_ino;
    } else {
        bash_meta.st_dev = 0;
        bash_meta.st_ino = 0;
    }

    // Try Zsh
    if (stat("/usr/bin/zsh", &st) == 0) {
        zsh_meta.st_dev = st.st_dev;
        zsh_meta.st_ino = st.st_ino;
    } else {
        zsh_meta.st_dev = 0;
        zsh_meta.st_ino = 0;
    }
}
// env | grep SHLVL

int is_tracked_shell(const char *cmd) {
    if (!cmd) return 0;

    char resolved[PATH_MAX];
    if (!realpath(cmd, resolved)) return 0;

    struct stat st;
    if (stat(resolved, &st) != 0) return 0;

    if ((st.st_dev == bash_meta.st_dev && st.st_ino == bash_meta.st_ino) ||
        (st.st_dev == zsh_meta.st_dev && st.st_ino == zsh_meta.st_ino)) {
        return 1;
    }
    return 0;
}

int exec_path(char *cmd, char **args, char **envp)
{
	
    if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
        update_shell_level(1);
    if (is_tracked_shell(cmd))
        update_shell_level(1);

    if (cmd[0] == '$')
    {
        char *value = get_env_var(cmd + 1, envp);
        if (strchr(value, '/'))
        {
            prepare_for_exec();
            execve(value, args, envp);
            my_fprintf(cmd, "No such file or directory\n");
            return (-1);
        }
        else
        {
            prepare_for_exec();
            execve(value, args, envp);
            my_fprintf(cmd, "command not found\n");
            return (-1);
        }
    }
    if (strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
        {
            if (access(cmd, X_OK) == 0)
            {
                prepare_for_exec();
                execve(cmd, args, envp);
                perror("execve failed 2");
                return -1;
            }
        }
    }

    if (is_system_path_command(cmd, envp))
    {

        if (exec_system_path(cmd, args, envp) == 0)
            return 0;
    }
    else
    {

        if (access(cmd, F_OK) == 0)
        {
            if (access(cmd, X_OK) == 0)
            {
                prepare_for_exec();
                execve(cmd, args, envp);

                if (errno == ENOEXEC)
                {
                    char *new_args[3];
                    new_args[0] = "/bin/bash";
                    new_args[1] = cmd;
                    new_args[2] = NULL;
                    prepare_for_exec();
                    execve(new_args[0], new_args, envp);
                }
                perror("execve failed 3\n");
                return (-1);
            }

            else
                return (perror("minishell"), -1);
        }
    }
    printf("command not found\n");
    return -1;
}