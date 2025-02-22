NAME	=  Bitcoin_Exchange
NAME_Debug = Debug
SRCS    := main.cpp
BIN		:= bin
OBJS    := $(addprefix $(BIN)/, $(SRCS:.cpp=.o))
INC		:= include

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I${INC}
CXXDEBUG	= -g

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

debug: CXXFLAGS += $(CXXDEBUG)
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME_Debug)

$(BIN)/%.o: %.cpp | $(BIN)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN):
	+@mkdir $(BIN)

clean:
	@rm -rf $(BIN)

fclean: clean
	@rm -f $(NAME) $(NAME_Debug)

re: fclean all

.PHONY: all clean fclean re