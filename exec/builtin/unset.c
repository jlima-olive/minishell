#include "../../sigma_minishell.h"

int builtin_unset(char **args)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *cur;
    t_os_envs *prev;
    size_t name_len;

    if (!args[1])
        return (-1);

    for (int i = 1; args[i]; i++)
    {
        name_len = strlen(args[i]);
        prev = NULL;
        cur = *env_list;

        while (cur)
        {
            int match = 0;

            // check linux_envs
            if (cur->linux_envs &&
                strncmp(cur->linux_envs, args[i], name_len) == 0 &&
                cur->linux_envs[name_len] == '=')
                    match = 1;
            if (cur->temp_vars &&
                strncmp(cur->temp_vars, args[i], name_len) == 0)
                    match = 1;
            if (match)
            {
                if (prev)
                    prev->next = cur->next;
                else
                    *env_list = cur->next;
                free(cur->linux_envs);
                free(cur->temp_vars);
                free(cur);
                break;
            }

            prev = cur;
            cur = cur->next;
        }
    }
	return (0);
}
