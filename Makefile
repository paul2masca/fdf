NAME        = fdf

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

CC        = gcc
FLAGS    = -Wall -Wextra -Werror 
FRAMEWORKS	=-framework OpenGL -framework AppKit
RM = rm -f

MLX_NAME	= libmlx.a
MLX_PATH	= ./mlx/$(MLX_NAME)

SRCS        =  gnl_utils.c gnl.c fdf.c ft.c matrix_utils.c matrix.c color.c \
				draw_utils.c draw.c controls.c \

INCLUDE		= fdf.h


%.o:	%.c
	@echo "$(BROWN)Compiling   ${BLUE}→   $(ORANGE)$< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c $< -o $@

OBJS        := $(SRCS:.c=.o)

all:		${NAME}

$(NAME): ${OBJS} $(INCLUDE) 
	@$(MAKE) -C mlx
	@$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm $(FRAMEWORKS)
	@echo "$(GREEN)$(NAME) created$(DEF_COLOR)"

clean:
	@${RM} $(OBJS) */*.o
	@${RM} $(NAME).dSYM
	@echo "$(BROWN)Successfully removed objects!$(DEF_COLOR)"

fclean:		clean
	@${RM} ${NAME}
	@${RM} ./mlx/libmlx.a
	@echo "$(BROWN)Successfully removed objects and binaries!$(DEF_COLOR)"

re:			fclean all

.PHONY:		all clean fclean re
