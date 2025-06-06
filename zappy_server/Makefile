##
## EPITECH PROJECT, 2025
## panoramix
## File description:
## Makefile
##

CC			=	gcc
CFLAGS		=	-Wall \
 				-Wextra \
 				-Werror \
 				-Wpedantic
CPPFLAGS	=	-iquote include
LDLIBS		=

SRC_DIR 	=	src/
OBJ_DIR		=	obj/
TEST_DIR	=	tests/

RM			?= 	rm -f

MAIN_SRC	=	$(SRC_DIR)main.c
MAIN_OBJ	=	$(MAIN_SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

SRC 		=	$(SRC_DIR)parser/arguments.c \
				$(SRC_DIR)parser/handlers/client_handler.c \
				$(SRC_DIR)parser/handlers/freq_handler.c \
				$(SRC_DIR)parser/handlers/help_handler.c \
				$(SRC_DIR)parser/handlers/port_handler.c \
				$(SRC_DIR)parser/handlers/size_handler.c \
				$(SRC_DIR)parser/handlers/teams_handler.c

OBJ			= 	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
TEST_SRC	=	$(TEST_DIR)tests.c
TEST_OBJ 	= 	$(TEST_SRC:$(TEST_DIR)%.c=$(OBJ_DIR)%.o)

NAME 		=   zappy_server
NAME_TEST	=	unit_tests

.PHONY: all clean fclean re valgrind

all: $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)%.o:	$(TEST_DIR)%.c	|	$(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $^ $(LDLIBS) -o $@

$(NAME_TEST): $(OBJ) $(TEST_OBJ)
	$(MAKE) -C ./lib/my
	$(CC) $^ $(LDLIBS) -o $@


valgrind: CFLAGS += -g3
valgrind: fclean all

tests_run: CFLAGS += --coverage
tests_run: LDLIBS += -lcriterion
tests_run: fclean $(NAME_TEST)

clean: tests_clean
	$(RM) vgcore.*
	$(RM) $(OBJ_DIR)*.o

tests_clean:
	$(RM) $(OBJ_DIR)*.gcno $(OBJ_DIR)*.gcda

fclean: clean
	$(RM) -r $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)

re: fclean all
