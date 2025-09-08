#include "../../sigma_minishell.h"

static int make_update_env(const char *str)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    size_t name_len = ft_strchr(str, '=') ? (size_t)(ft_strchr(str, '=') - str) : strlen(str);

    while (current)
    {
        if ((ft_strncmp(current->linux_envs[0], str, name_len) == 0)
            && current->linux_envs[0][name_len] == '=')
        {
            char *new_var = ft_strdup(str);
            if (!new_var)
                return (-1);
            free(current->linux_envs[0]);
            current->linux_envs[0] = new_var;
            return (0);
        }
        current = current->next;
    }

    t_os_envs *new_node = malloc(sizeof(t_os_envs));
    if (!new_node)
        return (-1);
    new_node->linux_envs = malloc(sizeof(char *) * 2);
    if (!new_node->linux_envs)
        return (free(new_node), -1);
    new_node->linux_envs[0] = ft_strdup(str);
    if (!new_node->linux_envs[0])                // <-- FIXED here!
        return (free(new_node->linux_envs), free(new_node), -1);
    new_node->linux_envs[1] = NULL;
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

void builtin_export(char **args)
{
    if (!args[1])
    {
        print_env_list();
        return;
    }
    for (int i = 1; args[i]; i++)
    {
        if (!strchr(args[i], '=')) 
        {
            add_temp_var(args[i]);
            continue;
        }
        if (make_update_env(args[i]) < 0)
            perror("minishell: export");
    }
}

