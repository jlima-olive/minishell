#include "../../sigma_minishell.h"

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
    new_node->linux_envs = ft_strdup(path);
    if (!new_node->linux_envs)
        return (free(new_node), NULL);
    new_node->next = NULL;
    new_node->temp_vars = NULL;
    return (new_node);
}

char **list_to_char(t_os_envs *envs)
{
    size_t count = 0;
    t_os_envs *temp = envs;
    char **final_char;
    size_t i = 0;
    while (temp)
    {
        if (temp->linux_envs)
            count++;
        temp = temp->next;
    }
    final_char = malloc(sizeof(char *) * (count + 1));
    if (!final_char)
        return (NULL);
    temp = envs;
    while (temp)
    {
        if (temp->linux_envs)
        {
            final_char[i] = ft_strdup(temp->linux_envs);
            if (!final_char[i])
            {
                free_matrix(final_char);
                free(final_char);
                return (NULL);
            }
            i++;
        }
        temp = temp->next;
    }
    final_char[i] = NULL;
    return (final_char);
}

void clear_env_list(void)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    t_os_envs *next;
    while (current)
    {
        next = current->next;
        free(current->linux_envs);
        free(current->temp_vars);
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
            printf("declare -x %s\n", current->linux_envs);
        if (current->temp_vars)
            printf("declare -x %s\n", current->temp_vars);
        current = current->next;
    }
}
void print_linux_env_list(void)
{
    t_os_envs *current = *get_env_list();

    while (current)
    {
        if (current->linux_envs)
                printf("%s\n", current->linux_envs);
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
        if (strncmp(env_list->linux_envs, key, key_len) == 0)
            return (env_list->linux_envs + key_len);
        env_list = env_list->next;
    }
    return NULL;
}


int add_temp_var(const char *str)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    t_os_envs *new_node;
    
    while (current)
    {
        if (current->temp_vars && strcmp(current->temp_vars, str) == 0)
            return (0);
        current = current->next;
    }
    new_node = malloc(sizeof(t_os_envs));
    if (!new_node)
        return (0);
    new_node->linux_envs = NULL;
    new_node->temp_vars = ft_strdup(str);
    if (!new_node->temp_vars)
    {
        free(new_node);
        return (-1);
    }
    new_node->next = NULL;

    if (*env_list == NULL)
        *env_list = new_node;
    else
    {
        current = *env_list;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    return (0);
}


char *find_temp_var(const char *key)
{
    t_os_envs *env = *get_env_list();
    size_t len = strlen(key);
    while (env)
    {
        if (env->temp_vars && ft_strncmp(env->temp_vars, key, len) == 0 && env->temp_vars[len] == '=')
            return (env->temp_vars + len + 1);
        env = env->next;
    }
    return (NULL);
}

int update_shell_level(int amount)
{
    t_os_envs *current = *get_env_list();
    int level = 0;

    // printf("Updating shell leveln\n"); 
    while (current)
    {
        if (current->linux_envs && strncmp(current->linux_envs, "SHLVL=", 6) == 0)
        {
            level = ft_atoi(current->linux_envs + 6);
            break ;
        }
        current = current->next;
    }
    level += amount;
    if (level < 0)
        level = 0;
    char *num = ft_itoa(level);
    if (!num)
        return (-1);
    char *final_str = malloc(strlen("SHLVL=") + strlen(num) + 1);
    if (!final_str)
        return (free(num), -1);
    strcpy(final_str, "SHLVL=");
    strcat(final_str, num);
    free(num);
    int result = make_update_env(final_str);
    free(final_str);
    return (result);
}

