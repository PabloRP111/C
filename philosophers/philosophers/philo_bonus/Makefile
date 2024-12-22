CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread
EXEC_BONUS = philo_bonus
SRCS_BONUS = philosopher_b.c val_args_b.c process.c thread_b.c aux_b.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(EXEC_BONUS)

bonus: $(EXEC_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(EXEC_BONUS)

fclean: clean
	rm -f $(EXEC_BONUS)

clean:
	rm -f $(OBJS_BONUS)

re: fclean all

.PHONY: fclean clean re all bonus

#-fsanitize=thread
#-g -O0 -pthread