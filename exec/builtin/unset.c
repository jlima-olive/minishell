#include "../../sigma_minishell.h"

void builtin_unset(char **args)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *cur;
    t_os_envs *prev;
    size_t name_len;

    if (!args[1])
        return;
    for (int i = 1; args[i]; i++)
    {
        name_len = strlen(args[i]);

        prev = NULL;
        cur = *env_list;
        while (cur)
        {
            if (strncmp(cur->linux_envs[0], args[i], name_len) == 0
                && cur->linux_envs[0][name_len] == '=')
            {
                // found the node
                if (prev)
                    prev->next = cur->next;
                else
                    *env_list = cur->next;

                free(cur->linux_envs[0]);
                free(cur->linux_envs);
                free(cur);
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
}
