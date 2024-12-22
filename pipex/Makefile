EXEC = pipex
EXEC_BONUS = pipex_bonus
CC=clang
CFLAGS= -Wall -Werror -Wextra -g
SRCS = build/pipex.c build/utils_pipex.c build/val_args_pipex.c \
	build/utils_extra_pipex.c build/another_utils_pipex.c
SRCS_BONUS = bonus/pipex_bonus.c bonus/utils_pipex_bonus.c \
    bonus/val_args_pipex_bonus.c bonus/utils_extra_pipex_bonus.c \
	bonus/another_utils_bonus.c bonus/here_doc.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
LIB = LIBDEF
LIBE = $(LIB)/libdef.a

all: $(EXEC) $(LIBE)

bonus: $(EXEC_BONUS) $(LIBE)

$(LIBE):
	make -C $(LIB)

$(EXEC): $(OBJS) $(LIBE)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) -L$(LIB) -ldef

$(EXEC_BONUS): $(OBJS_BONUS) $(LIBE)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(EXEC_BONUS) -L$(LIB) -ldef

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(EXEC) $(EXEC_BONUS)
	make -C $(LIB) fclean

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make -C $(LIB) clean

re: fclean all bonus

.PHONY: fclean clean re all bonus
