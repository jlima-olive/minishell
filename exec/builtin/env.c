#include "../../sigma_minishell.h"
#include <unistd.h>


t_os_envs **get_env_list(void)
{
    static t_os_envs *env_list = NULL;
    return &env_list;
}

static t_os_envs *create_env_node(char *path)
{
    t_os_envs *new_node = malloc(sizeof(t_os_envs));
    if (!new_node)
        return NULL;
    new_node->linux_envs = malloc(sizeof(char *) * 2);
    if (!new_node->linux_envs)
        return (free(new_node), NULL);
    new_node->linux_envs[0] = ft_strdup(path);
    new_node->linux_envs[1] = NULL;
    new_node->next = NULL;
    new_node->temp_vars = malloc(sizeof(char *));
    if (!new_node->temp_vars)
    {
        free(new_node->linux_envs[0]);
        free(new_node->linux_envs);
        free(new_node);
        return NULL;
    }
    new_node->temp_vars[0] = NULL;
    if (!new_node->linux_envs[0])
        return (free(new_node->linux_envs), free(new_node->temp_vars), free(new_node), NULL);
    return new_node;
}


void clear_env_list(void)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    t_os_envs *next;

    while (current) {
        next = current->next;
        if (current->linux_envs) {
            free(current->linux_envs[0]);
            free(current->linux_envs);
        }
        if (current->temp_vars) {
            for (int i = 0; current->temp_vars[i]; i++)
                free(current->temp_vars[i]);
            free(current->temp_vars);
        }
        free(current);
        current = next;
    }
    *env_list = NULL;
}


void print_env_list(void)
{
    t_os_envs *current = *get_env_list();

    while (current)
    {
        if (current->linux_envs)
        {
            for (int i = 0; current->linux_envs[i]; i++)
                printf("declare -x %s\n", current->linux_envs[i]);
        }
        if (current->temp_vars)
        {
            for (int i = 0; current->temp_vars[i]; i++)
                printf("declare -x %s\n", current->temp_vars[i]);
        }
        current = current->next;
    }
}
void print_linux_env_list(void)
{
    t_os_envs *current = *get_env_list();

    while (current)
    {
        if (current->linux_envs)
        {
            for (int i = 0; current->linux_envs[i]; i++)
                printf("%s\n", current->linux_envs[i]);
        }
        current = current->next;
    }
}

void builtin_env(char **env)
{
    extern char **environ;
    t_os_envs **env_list = get_env_list();
    t_os_envs *new_node;
    char **env_var = environ;
    clear_env_list();
    while (*env_var)
    {
        new_node = create_env_node(*env_var);
        if (!new_node)
        {
            perror("minishell: env");
            return;
        }
        new_node->temp_vars = malloc(sizeof(char *));
        if (!new_node->temp_vars)
        {
            perror("minishell: env (temp_vars)");
            free(new_node);
            return;
        }
        new_node->temp_vars[0] = NULL;

        if (*env_list == NULL)
            *env_list = new_node;
        else
        {
            t_os_envs *last = *env_list;
            while (last->next)
                last = last->next;
            last->next = new_node;
        }
        env_var++;
    }
    initialize_pwd(env);
}

void initialize_pwd(char **envp)
{
    char buf[1024];
    char *export_arg;
    char *args[3];
    char *pwd_value;

    pwd_value = find_path(envp, "PWD=");
    if (!pwd_value)
    {
        if (getcwd(buf, sizeof(buf)) == NULL)
        {
            perror("getcwd");
            return;
        }
        export_arg = malloc(strlen("PWD=") + strlen(buf) + 1);
        if (!export_arg)
            return;
        strcpy(export_arg, "PWD=");
        strcat(export_arg, buf);
        args[0] = "export";
        args[1] = export_arg;
        args[2] = NULL;
        builtin_export(args);
        free(export_arg);
    }
}

char *find_path_in_list(t_os_envs *env_list, const char *key)
{
    size_t key_len = strlen(key);

    while (env_list)
    {
        if (strncmp(env_list->linux_envs[0], key, key_len) == 0)
            return env_list->linux_envs[0] + key_len;
        env_list = env_list->next;
    }
    return NULL;
}


int add_temp_var(const char *str)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *envs = *env_list;

    if (!envs)
    {
        envs = malloc(sizeof(t_os_envs));
        if (!envs)
            return -1;
        envs->linux_envs = NULL;
        envs->temp_vars = malloc(sizeof(char *));
        if (!envs->temp_vars)
            return (free(envs), -1);
        envs->temp_vars[0] = NULL;
        envs->next = NULL;
        *env_list = envs;
    }
    int count = 0;
    while (envs->temp_vars && envs->temp_vars[count])
        count++;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(envs->temp_vars[i], str) == 0)
            return 0;
    }
    char **new_array = realloc(envs->temp_vars, sizeof(char *) * (count + 2));
    if (!new_array)
        return -1;
    envs->temp_vars = new_array;
    envs->temp_vars[count] = strdup(str);
    if (!envs->temp_vars[count])
        return -1;
    envs->temp_vars[count + 1] = NULL;
    return 0;
}

char *find_temp_var(const char *key)
{
    t_os_envs *envs = *get_env_list();
    if (!envs || !envs->temp_vars)
        return NULL;

    for (int i = 0; envs->temp_vars[i]; i++)
    {
        if (strcmp(envs->temp_vars[i], key) == 0)
            return envs->temp_vars[i];
    }
    return NULL;
}
