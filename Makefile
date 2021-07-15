NAME		=	philo_one
OBJS_PATH	=	objects/
SRCS_PATH	=	source/
HEAD_PATH	=	includes/
SRCS_LIST	= main.c init.c simulation.c utils.c
SRCS		=	$(addprefix $(SRCS_PATH), $(SRCS_LIST))	
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_PATH),$(OBJS_LIST))
RM			= 	rm -rf
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I $(HEAD_PATH)
DFLAGS		=	-g -Wall -Wextra -Werror -I $(HEAD_PATH)
MAKE_LIBFT	=	make -C libs/libft
LIBFT		=	libs/libft/libft.a

all: $(NAME) 
$(NAME): $(OBJS_PATH) $(OBJS) $(HEAD_PATH) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

debug:#-g -fsanitize=address
	$(CC)   $(DFLAGS) $(SRCS) $(LIBFT)  -o $(NAME)

$(LIBFT):
		$(MAKE_LIBFT)
$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c  $(HEAD_PATH)	
	$(CC) -I $(HEAD_PATH) $(OFLAGS) $< -o $@

test:
	$(CC) $(DFLAGS) test.c -o test
clean:
	$(MAKE_LIBFT) clean
	$(RM) $(OBJS_PATH)

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all
.PHONY: test
