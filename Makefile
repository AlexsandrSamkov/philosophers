NAME		=	philo
OBJS_PATH	=	objects/
SRCS_PATH	=	source/
HEAD		=	includes/philo.h
SRCS_LIST	= 	main.c init.c simulation.c utils.c
SRCS		=	$(addprefix $(SRCS_PATH), $(SRCS_LIST))	
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_PATH),$(OBJS_LIST))
RM			= 	rm -rf
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror  -I $(HEAD)

all: $(NAME) 
$(NAME): $(OBJS_PATH) $(OBJS) $(HEAD)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c  $(HEAD)	
	$(CC) $(CFLAGS) -c $(OFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
