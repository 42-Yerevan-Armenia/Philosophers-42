RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
BLUE	= \033[0;36m
SKY		= \033[1;36m

NAME		=	philo

SRCS		=	$(shell find "." -name "*.c")
				
OBJS		=	$(SRCS:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra

all:		$(NAME)

%.o: %.c $(NAME).h
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"
$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

clean:
	@echo "$(RED)♨️  clean  🗑$(RESET)"
	@$(RM) $(OBJS)

fclean:		clean
	@echo "$(RED)♨️  fclean 🗑$(RESET)"
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re