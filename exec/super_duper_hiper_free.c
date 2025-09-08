#include "../sigma_minishell.h"

void free_matrix(char **table)
{
    int i = 0;
    if (!table) return;
    while (table[i])
        free(table[i++]);
    free(table);
}
