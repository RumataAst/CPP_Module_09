NAME	=  btc
SRCS    := main.cpp BitcoinExchange.cpp struct_finance.cpp struct_time.cpp
BIN		:= bin
OBJS    := $(addprefix $(BIN)/, $(SRCS:.cpp=.o))
INC		:= include

# Compiler and flags
CXX			= c++
CXXFLAGS	= -g -Wall -Wextra -Werror -std=c++98 -I${INC}

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)


$(BIN)/%.o: %.cpp | $(BIN)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN):
	+@mkdir $(BIN)

clean:
	@rm -rf $(BIN)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re