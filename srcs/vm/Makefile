

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RED_B = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

ALL_C_ASM = asm.c add_args_code.c add_null_octets.c add_str_to_byte_code.c add_cec.c case_of_error.c \
		check_args.c check_name.c convert_labels_to_numbers.c convert_operations_to_byte_code.c \
		create_file.c do_parse.c encrypt_line.c fill_by_zeroes.c get_args.c initialize.c print_func.c \
		read_line.c read_operation.c wrong_end_of_line.c free_struct.c init_operations.c only_spaces.c add_arg.c op.c \
		check_name_and_comment.c getter.c have_end_quote.c put_after_quote.c read_.c

ALL_C_CW = $(wildcard *.c)


			
SRCDIR_ASM = ./srcs_asm
OBJDIR_ASM = ./objs_asm

SRCDIR_CW = .
OBJDIR_CW = ./objs_vm

ALL_OBJ_ASM = $(ALL_C_ASM:%.c=%.o)
OBJS_ASM = $(addprefix $(OBJDIR_ASM)/, $(ALL_OBJ_ASM))

ALL_OBJ_CW = $(ALL_C_CW:%.c=%.o)
OBJS_CW = $(addprefix $(OBJDIR_CW)/, $(ALL_OBJ_CW))
NAME_ASM = asm
NAME_CW = corewar

INCLUDES_ASM = ./includes/op.h ./includes/asm.h
INCLUDES_DIR = ../../includes
INCLUDES_CW = $(INCLUDES_DIR)/op.h $(INCLUDES_DIR)/vm.h $(INCLUDES_DIR)/vm_error.h


CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ../../libft_clala
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)

all: lib $(NAME_CW)

$(NAME_ASM): ./ft_printf/libft/libft.a $(OBJS_ASM)
	$(CC) $(FLAGS) $(OBJS_ASM) -L./ft_printf/libft -lft -o $@

$(OBJDIR_ASM):
	/bin/mkdir -p $(OBJDIR_ASM)

$(OBJDIR_ASM)/%.o: $(SRCDIR_ASM)/%.c $(INCLUDES_ASM) | $(OBJDIR_ASM)
	$(CC) $(FLAGS) -I./includes -I./ft_printf/libft/includes -c $< -o $@

$(NAME_CW): $(LIBFT) $(OBJS_CW)
	$(CC) $(FLAGS) $(OBJS_CW) -L $(LIBFT_DIR) -lft -o $@

$(OBJDIR_CW):
	/bin/mkdir -p $(OBJDIR_CW)

$(OBJDIR_CW)/%.o: $(SRCDIR_CW)/%.c $(INCLUDES_CW) | $(OBJDIR_CW)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

lib:
	$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR_CW)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME_CW)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re ft_printf
