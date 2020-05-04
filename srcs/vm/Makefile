# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/14 14:32:21 by sscottie          #+#    #+#              #
#    Updated: 2020/03/14 16:31:12 by sscottie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


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

ALL_C_CW = main.c \
			handle_error.c \
			input_validation.c \
			parse_player.c \
			t_carriage.c \
			t_carriages.c \
			t_mods.c \
			t_player.c \
			t_players.c \
			t_vm.c \
			t_vm_info.c \
			t_vs.c \
			print_debug.c \
			parse_args.c \
			print.c \
			handle_carriages.c \
			op.c \
			actions_1.c \
			actions_2.c \
			actions_3.c \
			actions_4.c \
			actions_handlers.c \
			check_operation.c \
			print_bits.c


			
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
INCLUDES_DIR = ../../includes/
INCLUDES_CW = $(INCLUDES_DIR)op.h $(INCLUDES_DIR)vm.h $(INCLUDES_DIR)vm_error.h

COMP_LIB = make -C ../../libft_clala/

FLAGS = -Wall -Wextra -Werror

LIBFT = ../../libft_clala/libft.a

all: lib $(NAME_CW)

$(NAME_ASM): ./ft_printf/libft/libft.a $(OBJS_ASM)
	gcc $(FLAGS) $(OBJS_ASM) -L./ft_printf/libft -lft -o $@

$(OBJDIR_ASM):
	/bin/mkdir -p $(OBJDIR_ASM)

$(OBJDIR_ASM)/%.o: $(SRCDIR_ASM)/%.c $(INCLUDES_ASM) | $(OBJDIR_ASM)
	gcc $(FLAGS) -I./includes -I./ft_printf/libft/includes -c $< -o $@

$(NAME_CW): $(LIBFT) $(OBJS_CW)
	gcc $(FLAGS) $(OBJS_CW) -L ../../libft_clala -lft -o $@

$(OBJDIR_CW):
	/bin/mkdir -p $(OBJDIR_CW)

$(OBJDIR_CW)/%.o: $(SRCDIR_CW)/%.c $(INCLUDES_CW) | $(OBJDIR_CW)
	gcc $(FLAGS) -I../../includes -I../../libft_clala/includes -c $< -o $@

lib:
	make -C ../../libft_clala/

clean:
	@/bin/rm -rf $(OBJDIR_ASM) $(OBJDIR_CW)
	@$(COMP_LIB) clean
	@$(COMP_PRINTF) clean

fclean: clean
	@/bin/rm -rf $(NAME_ASM) $(NAME_CW)
	@$(COMP_LIB) fclean
	@$(COMP_PRINTF) fclean

re: fclean all

.PHONY: lib clean fclean all re ft_printf
