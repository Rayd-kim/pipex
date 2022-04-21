NAME = pipex

CC = gcc

W = -Wall -Wextra -Werror

FILE = pipex.c \
		error.c \
		cmd_path.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c 

OBJS = $(FILE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft all
	$(CC) $(W) $(OBJS) -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) $(W) -c $< -o $@

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re