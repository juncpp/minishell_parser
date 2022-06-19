NAME = minishell

SRC = main.c minishell_llist.c minishell_init.c minishell_free_with_str.c minishell_lexer.c minishell_pre_parser.c minishell_parser_next.c \
		minishell_parser.c minishell_lexer_checks.c minishell_utils.c minishell_utils2.c minishell_signals.c

SRC_OBJ = $(SRC:%.c=%.o)

SRC_D = $(SRC:%.c=%.d)

CC = cc

CFLAGS = -MD -Wall -Wextra -Werror

FSA = -fsanitize=address

RM = rm -f

all : $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@

$(NAME): $(SRC_OBJ)
	$(CC) $(SRC_OBJ) $(FSA) -L$(shell brew --prefix readline)/lib -lreadline -o $@

clean: 
	$(RM) $(SRC_OBJ) $(SRC_D)

fclean: clean
	$(RM) $(NAME)

-include $(SRC_D)

re: fclean all

.PHONY: all clean fclean re