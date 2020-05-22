SRCDIR_ASM = srcs/asm
OBJDIR_ASM = objs/asm

SRCDIR_CW = srcs/vm
OBJDIR_CW = objs/vm

ALL_C_ASM = $(wildcard $(SRCDIR_ASM)/*.c)
ALL_C_CW = $(wildcard $(SRCDIR_CW)/*.c)

OBJS_ASM = $(patsubst $(SRCDIR_ASM)/%.c,$(OBJDIR_ASM)/%.o,$(ALL_C_ASM))
OBJS_CW = $(patsubst $(SRCDIR_CW)/%.c,$(OBJDIR_CW)/%.o,$(ALL_C_CW))

NAME_ASM = asm
NAME_CW = corewar

INCLUDES_ASM = ./includes/op.h ./includes/asm.h	./includes/asm_error.h
INCLUDES_CW = ./includes/op.h ./includes/vm.h ./includes/vm_error.h ./includes/vs_consts.h

LIBFT_DIR = ./libft_clala
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME_ASM) $(NAME_CW)

$(NAME_ASM): $(LIBFT) $(OBJS_ASM)
	$(CC) $(FLAGS) $(OBJS_ASM) -L$(LIBFT_DIR) -lft -o $@

$(OBJDIR_ASM):
	/bin/mkdir -p $(OBJDIR_ASM)

$(OBJDIR_ASM)/%.o: $(SRCDIR_ASM)/%.c $(INCLUDES_ASM) | $(OBJDIR_ASM)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes -c $< -o $@

$(NAME_CW): $(LIBFT) $(OBJS_CW)
	$(CC) $(FLAGS) $(OBJS_CW) -L $(LIBFT_DIR) -lft -o $@

$(OBJDIR_CW):
	/bin/mkdir -p $(OBJDIR_CW)

$(OBJDIR_CW)/%.o: $(SRCDIR_CW)/%.c $(INCLUDES_CW) | $(OBJDIR_CW)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes -c $< -o $@

$(LIBFT): lib

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR_ASM) $(OBJDIR_CW)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME_ASM) $(NAME_CW)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re