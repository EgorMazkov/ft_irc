NAME			=	ircserver

CC				=	c++

CDEBUG			=	 -Wall -Wextra -Werror -std=c++98

SRC				=	srcs/main.cpp

OBJ				=	$(SRC:.cpp=.o)
OBJ_DIR			=	./objs/
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ))

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					@$(CC) -o $@ $^
					@echo "\033[32m"Make DONE

$(OBJ_DIR)%.o	:	%.cpp
					@mkdir -p $(OBJ_DIR)
					@$(CC) -c $< -o $@

.PHONY			:	all fclean clean re

clean			:
				@rm -rf $(OBJ_DIR)
				@echo "\033[32m"clean DONE

fclean			:	clean
				@rm -rf $(NAME)
				@echo "\033[32m"fclean DONE

re				:	fclean all