NAME			=	ircserv

CC				=	c++

CDEBUG			=	 -Wall -Wextra -Werror -std=c++98 -g

SRC				=	Server.cpp		main.cpp

OBJ				=	$(SRC:.cpp=.o)
OBJ_DIR			=	../objs/
OBJS			=	$(OBJ)

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