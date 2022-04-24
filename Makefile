NAME = pipex

CC = gcc

W = -Wall -Wextra -Werror

FILE = pipex.c \
		error.c \
		cmd_path.c \
		file_open.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c 

FILE_B = pipex_bonus.c \
			error_bonus.c \
			cmd_path_bonus.c \
			file_open_bonus.c \
			./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c
CHECK = 1

OBJS = $(FILE:.c=.o)

OBJS_B = $(FILE_B:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_B)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(MAKE) -C ./libft all
	$(CC) $(W) $(OBJECTS) -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) $(W) -c $< -o $@

bonus : $(OBJS_B)
	make WITH_BONUS=1 all

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)
	rm -rf $(OBJS_B)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus