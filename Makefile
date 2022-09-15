#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME		= minishell

FLAGS		= -Wall -Wextra -Werror -g3
INCLUDE		= -I $(HEAD_DIR) -L/usr/include -lreadline
CC			= gcc

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRC_DIR		=	srcs/
SRCS		=	$(addprefix $(SRC_DIR), $(SRC_FILE))
SRC_FILE	=	minishell.c				\
				\
				parsing/parse_lexer.c	\
				parsing/main_parser.c	\
				parsing/split_cmds.c	\
				parsing/expender.c		\
				parsing/heredoc.c		\
				parsing/lexer.c			\
				parsing/utils.c			\
				\
				builtin/ft_export.c	\
				builtin/ft_unset.c	\
				builtin/ft_echo.c		\
				builtin/ft_exit.c		\
				builtin/ft_env.c		\
				builtin/ft_pwd.c		\
				builtin/ft_cd.c		\
				\
				exec/builtin_finder.c	\
				exec/ft_tabstradd.c		\
				exec/single_cmd.c		\
				exec/my_args.c			\
				exec/execute.c			\
				exec/my_env.c			\
				\
				tools/garbage_manager.c	\
				tools/env.c

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_DIR		= obj/
OBJ			= $(SRC_FILE:.c=.o)

#------------------------------------#
#              INCLUDES              #
#------------------------------------#

HEADER		= $(addprefix $(HEAD_DIR), $(HEAD_FILE))
HEAD_DIR	= includes/
HEAD_FILE	= proto.h struct.h

LIBFT		= $(addprefix $(LIB_DIR), $(LIBFT_A))
LIB_DIR		= libft/
LIBFT_A		= libft.a


NONE		= "\033[0m"
GREEN		= "\033[32m"
YELLOW		= "\033[33m"
GRAY		= "\033[2;37m"
CURSIVE		= "\033[3m"

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(GREEN) "     ~ Making $(LIB_DIR)..." $(END)
	make -C $(LIB_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(INCLUDE) -I includes -o $(NAME)
	@echo $(GREEN)"- Project compiled -"$(NONE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)/parsing/ $(OBJ_DIR)/main/ $(OBJ_DIR)/tools/ $(OBJ_DIR)/exec/ $(OBJ_DIR)/builtin/ 
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@ -I includes


clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	make clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -f $(NAME)
	make fclean -C $(LIB_DIR)
	@echo $(YELLOW)"- Project removed -"$(NONE)

re: fclean all

.PHONY : clean fclean re