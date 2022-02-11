NAME		= so_long
HEADER		= so_long.h
HEADER_DIR	= ./include

SRCS		= so_long_utils1.c so_long_utils2.c so_long_utils3.c so_long.c \
			main.c
SRC_DIR		= ./srcs

OBJS		= $(SRCS:.c=.o)
OBJ_DIR		= ./objs

GCC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
MLXFLAGS	= -lmlx -lXext -lX11
VAL			= valgrind -s --leak-check=full
MKDIR		= mkdir
MAP			= ./maps/map1.ber

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(GCC) -o $@  $(addprefix $(OBJ_DIR)/, $(OBJS)) $(MLXFLAGS)

%.o: ./srcs/%.c ./include/$(HEADER)
	$(GCC) -c $(CFLAGS) $< -o $(OBJ_DIR)/$@

bonus:

debug:
	$(GCC) $(CFLAGS) $(SRC_DIR) $(MLXFLAGS)

leaks: $(NAME)
	$(VAL) ./$(NAME) $(MAP)

$(OBJ_DIR):
	$(MKDIR) -p $@

clean:
	$(RM)  $(addprefix $(OBJ_DIR)/, $(OBJS))
	$(RM) -r ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
