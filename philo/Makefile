SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=build/%.o)
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
BUILD_DIR = build
EXEC = philo

all: $(BUILD_DIR) $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

build/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC) 5 800 200 200

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(EXEC)
	@rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all run clean fclean re
