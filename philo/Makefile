SRC_DIR         = src/
OBJ_DIR         = objs/
INC_DIR         = header/

SRC_FILES       =	main.c				\
					parsing.c			\
					error.c				\
					utils.c				\
					init.c				\
					mutex_handling.c	\
					time.c				\
					free.c				\
					print_mutex.c		\
					threads.c			\
					routines.c			\
					monitor.c			\
					phil_alone.c		\
					fork_management.c	\

SOURCES         = $(addprefix $(SRC_DIR), $(SRC_FILES)) \

OBJS            = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \

HEADER          = $(INC_DIR)philo.h
NAME            = philo

CC              = cc
FLAGS           = -Wall -Wextra -Werror -I$(INC_DIR)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(HEADER) Makefile
	$(CC) $(FLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
