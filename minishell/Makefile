CC = clang
CFLAGS = -Wall -Wextra -Werror
EXEC = minishell
SRCS = minishell.c parsing/parsing.c parsing/alloc_mem.c parsing/expand_line.c \
	parsing/finish_quotes.c utils/utils_garbage.c utils/errors.c \
	utils/utils.c utils/utils2.c utils/utils3.c\
	builds/echo.c builds/env.c builds/exit.c builds/export.c \
	builds/export_utils.c builds/pwd.c builds/unset.c builds/cd.c \
	execution/decide_cmd.c parsing/close_quotes.c \
	parsing/heredocs.c execution/signals.c execution/check_orders.c \
	execution/sigactions.c execution/signals2.c execution/check_redirs.c\
	parsing/expand_heredoc.c utils/utils4.c parsing/sintax.c utils/utils5.c 
	 
OBJS = $(SRCS:.c=.o)
LIB = Libft
LIBDEF = $(LIB)/libft.a

all: $(EXEC)

$(LIBDEF):
	make -C $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) $(LIBDEF)
	@mkdir -p ./temps
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) -L$(LIB) -lft -lreadline 

clean:
	rm -f $(OBJS)
	make -C $(LIB) clean

fclean: clean
	rm -f $(EXEC)
	@-rm -rf ./temps
	make -C $(LIB) fclean

re: fclean all

.PHONY: fclean clean re all
