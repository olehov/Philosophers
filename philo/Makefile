SRCS = $(wildcard *.c)
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc

all:
	$(CC) $(CFLAGS) $(SRCS)

run_leaks:
	@rm -f a.out
	$(CC) $(CFLAGS) $(SRCS)
	valgrind --tool=helgrind -s --history-level=approx --log-file=valgrind-out.txt ./a.out 5 800 100 200 5

run_valgrind:
	@rm -f a.out
	$(CC) $(CFLAGS) $(SRCS)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s --log-file=valgrind-out.txt ./a.out 5 800 100 200 5


run:
	@rm -f a.out
	$(CC) $(CFLAGS) $(SRCS)
	./a.out 2 310 200 100


clean:
	@rm -f a.out

fclean:
	@rm -f a.out

.PHONY: all make_leaks clean fclean re