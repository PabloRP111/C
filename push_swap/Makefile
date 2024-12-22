EXEC = push_swap
EXECB = checker
CC=clang
CFLAGS= -Wall -Werror -Wextra
SRCS = push_swap.c fill_list.c push_swap_utils.c fill_list_mult_args.c \
		push_swap_utils_extra.c make_moves.c order_moves.c moves.c \
		manage_rotate.c calc_costs.c choose_move.c short_five.c
SRCSB = checker.c fill_list_mul_b.c push_swap_utils_bonus.c \
		make_moves_bonus.c moves_bonus.c fill_list_b.c \
		push_swap_utils_extra_b.c
OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)
LIB = LibDEF
LIBDEF = $(LIB)/libdef.a

all: $(EXEC)

$(LIBDEF):
	make -C $(LIB)

$(EXEC): $(OBJS) $(LIBDEF)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) -L$(LIB) -ldef

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(EXEC)
	rm -f $(EXECB)
	make -C $(LIB) fclean

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)
	make -C $(LIB) clean

re: fclean all

bonus: $(EXECB)

$(EXECB): $(OBJSB) $(LIBDEF)
	$(CC) $(CFLAGS) $(OBJSB) -o $(EXECB) -L$(LIB) -ldef

.PHONY: fclean clean re all bonus
