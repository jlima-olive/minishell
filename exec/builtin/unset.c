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
            if (cur->linux_envs && cur->linux_envs[0] &&
                strncmp(cur->linux_envs[0], args[i], name_len) == 0 &&
                cur->linux_envs[0][name_len] == '=')
            {
                if (prev)
                    prev->next = cur->next;
                else
                    *env_list = cur->next;

                free(cur->linux_envs[0]);
                free(cur->linux_envs);
                free(cur);
                break;
            }
            if (cur->temp_vars)
            {
                for (int j = 0; cur->temp_vars[j]; j++)
                {
                    if (strcmp(cur->temp_vars[j], args[i]) == 0)
                    {
                        free(cur->temp_vars[j]);

                        // shift
                        int k = j;
                        while (cur->temp_vars[k]) {
                            cur->temp_vars[k] = cur->temp_vars[k + 1];
                            k++;
                        }

                        // shrink allocation
                        char **shrunk = realloc(cur->temp_vars, sizeof(char *) * k);
                        if (shrunk)
                            cur->temp_vars = shrunk;

                        break;
                    }
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
}

