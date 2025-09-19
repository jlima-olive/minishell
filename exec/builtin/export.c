#include "../../sigma_minishell.h"

int make_update_env(const char *str)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    size_t len = ft_strchr(str, '=') ? (size_t)(ft_strchr(str, '=') - str) : strlen(str);
    // existing variable with the same name
    while (current)
    {
        if (current->linux_envs && ft_strncmp(current->linux_envs, str, len) == 0 && current->linux_envs[len] == '=')
        {
            char *new_var = ft_strdup(str);
            if (!new_var)
                return (-1);
            free(current->linux_envs);
            current->linux_envs = new_var;
            return (0);
        }
        current = current->next;
    }
    // Not found
    t_os_envs *new_node = malloc(sizeof(t_os_envs));
    if (!new_node)
        return (-1);
    new_node->linux_envs = ft_strdup(str);
    if (!new_node)
        return ((free(new_node)), -1);
    new_node->temp_vars = NULL;
    new_node->next = NULL;
    if (!*env_list)
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

int builtin_export(char **args)
{
    printf( "==CALLING EXPORT STUFF\n");
    if (!args[1])
    {
        print_env_list();
        return (0);
    }
    for (int i = 1; args[i]; i++)
    {
        if (!strchr(args[i], '=')) 
        {
            add_temp_var(args[i]);
            continue;
        }
        if (make_update_env(args[i]) < 0)
            return (perror("minishell: export"), 0);
    }
	return (1);
}

