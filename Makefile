NAME	=	philo

SRC_DIR	=	sources
UTILS	=	utils/
PATH_OBJ	=	objects

CC	=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
THREAD	=	-pthread
RM	=	rm -rf

SRC_FILES	=	philosophers.c \
				$(UTILS)settings.c \
				$(UTILS)creat_list.c \
				$(UTILS)ft_atoi.c \
				$(UTILS)ft_isdigit.c \
				$(UTILS)ft_strchr.c
INCLUDES	=	-I ./includes

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ	=	$(SRC:$(SRC_FILES)/%.c=$(PATH_OBJ)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(THREAD) $(OBJ) -g3 -o $(NAME) $(INCLUDES)

$(PATH_OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) -g3 -o $@ $<

clean:
	@$(RM) $(PATH_OBJ)
	@echo obj removed

fclean: clean
	@$(RM) $(NAME)
	@echo clean everything

re: fclean all

#./philo 3 2 300 3 5 

.PHONY: all clean fclean re