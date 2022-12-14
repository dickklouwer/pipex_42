
#= Vars =#

NAME := pipex

SRCS := pipex.c parse_path.c

SRCSDIR := srcs

OBJDIR := obj

OBJ := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

CFLAGS := -Wall -Wextra -g

LIBFT := libft

INCLUDES := -I $(LIBFT) -I includes 

#= COLORS =#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#= Targets =#

all: libft $(NAME)

libft:
	@echo "$(GREEN)Building libft ...$(RESET)"
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Building pipex ...$(RESET)"
	@$(CC) $(OBJ) libft/libft.a $(INCLUDES) -o pipex

$(OBJDIR)/%.o: $(addprefix $(SRCSDIR)/, %.c)
	@echo "$(GREEN)Building object files ...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning ...$(RESET)"
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME) $(OBJDIR)

re: fclean all