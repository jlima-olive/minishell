#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_type{
    CMD,
    AND,
    OR,
	EMPTY,
	ERROR
}   t_type;

#endif

