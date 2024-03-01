#SETUP
NAME		=	philo
CC			=	gcc -pthread
FLAGS		=	-Wall -Wextra -Werror
CPPFLAGS	:=	-I includes

#CC			=	gcc -g -pthread
#FLAGS += -fsanitize=pthread
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	philo.h 
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))
SRCS		=	main.c init_fork.c init_rules.c\
				time.c clean.c engine.c util.c \
				process.c routine_fork.c monitor.c \
				init_mutex.c routine_philo.c

SRC_DIR		=	src/
SRC_PATH	=	$(addprefix $(SRC_DIR), $(SRCS))
OBJ_DIR		=	obj/
OBJ       	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_PATH))

#LIB
LIB = -lpthread

# Create obj folder if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

#COMMANDS
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile
				@${CC} ${FLAGS} $(CPPFLAGS) -c $< -o $@

all:			$(NAME)

# Test 1 800 200 200. The philosopher should not eat and should die.
test1: all
			echo Testing One philosopher -- The philosopher should not eat and should die.
			./philo 1 800 200 200
# Test 5 800 200 200. No philosopher should die.
test2: all
			echo Testing five philosopher -- No philosopher should die.
			./philo 5 800 200 200
# Test 5 800 200 200 7. No philosopher should die and the simulation should stop
#when every philosopher has eaten at least 7 times.
test3: all
			echo Testing five philosopher 7 meals -- No philosopher should die and the simulation should stop
			./philo 5 800 200 200 7
# Test 4 410 200 200. No philosopher should die.
test4: all
			echo Testing no philosopher should die -- No philosopher should die.
			./philo 4 410 200 200
# Test 4 310 200 100. One philosopher should die.
test5: all
			echo  One philosopher should die.
			./philo 4 310 200 200

# Test 1 800 200 200. The philosopher should not eat and should die.
# Test 5 800 200 200. No philosopher should die.
# Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
# Test 4 410 200 200. No philosopher should die.
# Test 4 310 200 100. One philosopher should die.

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) 
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
				@$(RM) $(OBJ)
				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@rm $(NAME)
				@echo -e "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:			all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m