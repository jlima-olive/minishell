PROJ=		minishell

NAME=		${PROJ}.a

PARSER_DIR=	parse

PARSER=		$(PARSER_DIR)/$(PARSER_DIR).a

EXEC_DIR=	exec

BIN_DIR=	$(EXEC_DIR)/builtin

EXEC=		$(wildcard ${EXEC_DIR}/*.c) \
			$(wildcard ${BIN_DIR}/*.c)

CC=			cc

AR=			ar rcs

CFLAGS=		-Wall -Wextra -Werror

PIPEX       = pipex
PIPEX_BONUS = pipex_bonus

PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft
BULTIN_DIR  = builtin
BULTIN_SRCS = $(wildcard $(BULTIN_DIR)/*.c)

all: exec_rule parse_rule $(PROJ)

$(PROJ): $(PROJ).c
	$(CC) -lreadline -lncurses $(PROJ).c ${EXEC} $(PARSER) $(PARSER_DIR)/jojo_libft.a $(EXEC_DIR)/$(PIPEX_DIR)/$(PIPEX).a $(EXEC_DIR)/$(LIBFT_DIR)/libft.a -o $(PROJ) -lncurses -lreadline

parse_rule:
	$(MAKE) -C $(PARSER_DIR)

exec_rule: 
	$(MAKE) -C $(EXEC_DIR)

clean:
	rm -f ${OBJ_FILES} ${NAME}
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(EXEC_DIR) clean

fclean: clean
	rm -f $(PROJ)
	$(MAKE) -C $(PARSER_DIR) fcleanlocal
	$(MAKE) -C $(EXEC_DIR) fclean

re: fclean all
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(EXEC_DIR)

r: fclean all
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(EXEC_DIR)
	./minishell

.PHONY: re fclean clean all exec_rule parse_rule

# so:
