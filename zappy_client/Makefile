##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

GREEN		= \033[0;32m
RESET		= \033[0m
BLUE		= \033[94m
RED		   	= \033[91m
YELLOW		= \033[93m

CXX					?= 		g++

CXXFLAGS			=		-std=c++17

LDFLAGS				=		-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM 					?= 		rm -f

BUILD_DIR			=		./build

SRC					=		Source/Main.cpp								\
							Source/NetworkManager/NetworkManager.cpp 	\
							Source/ArgumentsHandler/Arguments.cpp		\
							Source/Client/Client.cpp					\
							Source/Raylib/Core/Window.cpp		\
							Source/Raylib/Core/Input.cpp		\
							Source/Raylib/Graphics/Camera.cpp	\
							Source/Raylib/Graphics/Texture.cpp	\
							Source/Raylib/Graphics/Material.cpp	\
							Source/Raylib/Graphics/Shapes.cpp	\
							Source/Raylib/UI/Widget.cpp			\
							Source/Raylib/UI/Label.cpp			\
							Source/Raylib/UI/Button.cpp			\
							Source/Raylib/Utils/Math.cpp

NAME				=		zappy_gui

CPPFLAGS			=		-iquote Source -Wall -Wextra

OBJ 				=		$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf "$(GREEN)[OK]$(RESET) $(YELLOW)Building $<...$(RESET)\n"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

all:$(NAME)


$(NAME): $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)
	@printf "$(GREEN)[OK]$(RESET) $(BLUE)Project built successfully$(RESET)\n"
	@printf "$(GREEN)[OK] Project Build [OK]$(RESET)\n"


clean:
	@printf "$(GREEN)[OK]$(RESET) $(RED)Cleaning project...$(RESET)\n"
	@$(RM) $(OBJ)

fclean: clean
	@printf "$(GREEN)[OK]$(RESET) $(RED)Removing project...$(RESET)\n"
	@$(RM) $(NAME)
	@$(RM) $(TEST_NAME)

re: fclean all

debug_asan: CPPFLAGS += -g3 -fsanitize=address
debug_asan: LDFLAGS += -fsanitize=address
debug_asan: fclean all

debug_valgrind: CPPFLAGS += -g3
debug_valgrind: fclean all

.PHONY: all clean fclean re debug_asan debug_valgrind
