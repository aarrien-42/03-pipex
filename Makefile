# Normbre del ejecutable
NAME = pipex

# Directorios
OBJ_DIR = objs/
OBJF = objs

# Ficheros
SRC_FILES = ft_pipex ft_pipex_utils ft_fill
SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))

# Comandos
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address -g3
RM = rm -f
AR = ar rcs

.SILENT:

# REGLAS #
all: $(NAME)

# Compilar conjuntamente y meter los objs en su carpeta correspondiente
$(NAME): $(OBJ) | $(OBJF)
	@$(MAKE) -C ./libft
	@echo "libft compiled!"
	@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	@echo "pipex compiled!"
	@mv $(OBJ) $(OBJ_DIR)
	@echo "Objects moved to objs file"

# Compilar objetos individualmente
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Crear directorio temporal para los obj
$(OBJF):
	@mkdir -p $(OBJ_DIR)

# Eliminar temporales
clean:
	@$(MAKE) -C ./libft clean
	@$(RM) -r $(OBJ_DIR)
	@echo "Objects and directory cleaned!"

# Eliminar temporales y ejecutable
fclean: clean
	@$(MAKE) -C ./libft fclean
	@$(RM) $(NAME) libft.a
	@echo "Executable cleaned!"

re: fclean all

norm:
	@norminette

.PHONY: all clean fclean re
