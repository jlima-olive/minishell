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
    
    new_node->linux_envs = malloc(sizeof(char *) * 2);
    if (!new_node->linux_envs)
        return (free(new_node), NULL);
    
    new_node->linux_envs[0] = ft_strdup(path);
    new_node->linux_envs[1] = NULL;
    new_node->next = NULL;
    
    if (!new_node->linux_envs[0])
        return (free(new_node->linux_envs), free(new_node), NULL);
    
    return new_node;
}

void clear_env_list(void)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    t_os_envs *next;

    while (current) {
        next = current->next;
        free(current->linux_envs[0]);
        free(current->linux_envs);
        free(current);
        current = next;
    }
    *env_list = NULL;
}

void print_env_list(void)
{
    t_os_envs *current = *get_env_list();
    while (current) {
        ft_putstr_fd(current->linux_envs[0], 1);
        current = current->next;
    }
}

void builtin_env(void)
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
}