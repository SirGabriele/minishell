NAME = minishell 

LIBFT = libft/libft.a

SRC = main.c					\
	prompt.c					\
	launch_program.c			\
	highlight_syntax_error.c	\
	free_program.c

SIGNALS = signals_one.c

CHECK =	get_missing_user_input.c	\
	check_paired_characters.c		\
	ft_check_quotes.c				\
	ft_check_forbidden_characters.c	\
	ft_check_isolated_ampersands.c

EXEC =	simulate_structs.c	\
	print_structs.c			\
	start_recursive.c		\
	handle_all_redirs.c		\
	heredoc_requested.c		\
	execute_cmd.c

LL = ft_lstnew_env_entry.c	\
	ft_create_node.c

INIT = init_root_struct.c

UTILS =	what_is_index_in.c	\
	convert_env_into_ll.c	\
	convert_env_into_arr.c

SRCS = $(addprefix src/, $(SRC))			\
	$(addprefix src/signals/, $(SIGNALS))	\
	$(addprefix src/check/, $(CHECK))		\
	$(addprefix src/utils/, $(UTILS))		\
	$(addprefix src/ll/, $(LL))				\
	$(addprefix src/init/, $(INIT))			\
	$(addprefix src/exec/, $(EXEC))

CC = clang

FLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~     Clean terminated!     ~"
	@echo "*         mihishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -f $(NAME)

re: fclean all

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -Llibft -lft -Ilibft $(READLINE) -o $(NAME)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*         minishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

$(LIBFT):
	@make -C libft --no-print-directory

.PHONY: all clean fclean re
