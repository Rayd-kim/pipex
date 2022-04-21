NAME = pipex

CC = gcc

W = -Wall -Wextra -Werror

FILE = pipex.c \
		error.c \
		cmd_path.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c 

FILE_B = pipex_bonus.c \
			error.c \
			cmd_path.c \
			./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c

OBJS = $(FILE:.c=.o)

OBJS_B = $(FILE_B:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft all
	$(CC) $(W) $(OBJS) -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) $(W) -c $< -o $@

bonus : $(OBJS_B)
	$(CC) $(W) $(OBJS_B) -L./libft -lft -o $(NAME)

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)
	rm -rf $(OBJS_B)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus